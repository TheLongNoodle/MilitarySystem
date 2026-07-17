# Part 3 — Work Plan and Change Log

This document describes everything that was done for Part 3 of the course project,
mapped to the assignment requirements (sections א–ז of חלק 3), with the reasoning
behind each change and how it was verified.

## Work plan

| # | Requirement | What was done | Status |
|---|-------------|---------------|--------|
| 1 | (א) Generic linked list with templates | New `src/LinkedList.h` | Done |
| 2 | (ג) Replace dynamically-allocated `char*` fields with `std::string` | All 8 classes converted | Done |
| 3 | (ב) Replace one array with the linked list; (ד) replace the rest with an STL container | Officer → `LinkedList`; all others → `std::vector` | Done |
| 4 | (ה) Delete rule-of-three/five members that are no longer needed | Destructors/copy-deletes pruned per class (table below) | Done |
| 5 | (ו) Managing class as Singleton | `MilitarySystem::getInstance()` (Meyers singleton) | Done |
| 6 | (ז) At least 2 more design patterns | Factory (`VehicleFactory`) + Observer (`MissionObserver`), plus Iterator on the list | Done |
| 7 | Update `main.cpp` and the `.vcxproj` project files | Done | Done |
| 8 | Build with zero warnings and run regression + edge tests | Verified (see "Verification") | Done |
| 9 | This document | — | Done |

## Requirement א — generic linked list (`src/LinkedList.h`, new file)

A template singly linked list with head/tail pointers, implemented without any STL
types, supporting exactly what the assignment allows:

- `addToEnd(value)` — O(1) using the tail pointer.
- `remove(value)` — removes the first node equal to `value`; correctly handles
  removing the head, the tail, and the last remaining node (tail pointer is reset).
- `print()` — streams elements with `operator<<`, comma-separated.

The list owns its nodes (destructor frees them; copy construction/assignment are
deleted to prevent double-free). It also exposes a minimal `ConstIterator`
(`begin`/`end`, `*`, `++`, `!=`) — the **Iterator design pattern** — so an owner can
traverse elements for display without the list knowing how to render them.

## Requirement ב — one array replaced by the linked list

`Officer::commandedSoldiers` changed from a manual `Soldier**` array (with
`commandedCount`/`commandedCapacity` and grow-by-doubling code) to
`LinkedList<Soldier*>`. The duplicate-check, add, remove and print logic now runs
through the list; ~40 lines of manual array management were deleted, along with
`Officer`'s destructor.

To make this feature actually reachable (in Part 2 no menu operation ever called
`addCommandedSoldier`), a new menu option was added: **14. Assign soldier to
officer's command** → `MilitarySystem::assignSoldierToOfficer(officerPN, soldierPN)`,
which verifies via `dynamic_cast` that the target really is an `Officer`.
`Officer::print()` now also prints the commanded-soldiers list when not empty.

## Requirement ג — `char*` → `std::string`

Every dynamically-allocated `char*` field was replaced with `std::string`:

| Class | Fields converted |
|-------|------------------|
| `Soldier` | `name`, `role` |
| `Unit` | `unitName` |
| `Vehicle` | `vehicleNumber` |
| `Mission` | `missionName` |
| `Equipment` | `name`, `serialNumber` |
| `Warehouse` | `name` |

Consequences applied throughout:

- Getters return `const std::string&`; setters and constructor parameters take
  `const std::string&` (string treated as an object, never passed by value).
- Empty-input validation became `value.empty()`.
- `strcmp` comparisons in the find methods became `==` on strings.
- `src/Utils.h` (`utils::dupString`, including its `#pragma warning(disable: 4996)`
  hack) was **deleted** — nothing uses it anymore.
- The manual exception-safety gymnastics in constructors (allocate `name`, try to
  allocate `role`, free `name` on failure) disappeared: `std::string` members are
  released automatically by their own destructors if a constructor throws.

## Requirement ד — remaining arrays → `std::vector`

All other manual `T**`+count+capacity arrays became `std::vector<T*>`:

| Class | Array replaced |
|-------|----------------|
| `MilitarySystem` | `soldiers`, `units`, `missions` (heterogeneous vectors of base-class pointers) |
| `BaseFacility` | `vehicles` (heterogeneous), `warehouses` |
| `Unit` | `soldiers` |
| `Warehouse` | `equipmentList` |
| `Jeep` | `passengers` |
| `Truck` | `loadedEquipment` |
| `LogisticsMission` | `requiredEquipment` |

Style rules from the course checklist were followed:

- **No size/capacity variables kept next to a container** — counts come from
  `size()`. (`Jeep::maxPassengers` remains: it is a domain rule — seating capacity —
  not container bookkeeping.)
- **No index-based traversal** — internal loops use range-`for`; membership tests
  and removals use `std::find` from `<algorithm>`.
- Seven copies of the grow-the-array boilerplate (~15 lines each) were deleted.

## Requirement ה — pruning the unneeded rule-of-three/five members

(No move operations existed in the code base, so "the five" reduces to the three.)

**Removed** because `std::string`/`std::vector`/`LinkedList` members now clean up
after themselves:

| Class | Removed |
|-------|---------|
| `Equipment` | `~Equipment()` and both deleted copy operations — the class is now safely copyable (rule of zero) |
| `Soldier` | destructor body → `virtual ~Soldier() = default;` (must stay virtual: polymorphic base of `Officer`) |
| `Vehicle` | destructor body → `virtual ~Vehicle() = default;` (polymorphic base) |
| `Mission` | destructor body → `virtual ~Mission() = default;` (polymorphic base) |
| `Unit`, `Officer`, `Jeep`, `Truck`, `LogisticsMission` | destructors removed entirely |
| `Officer`, `Jeep`, `Truck`, `ArmoredTransport`, `TrainingMission`, `LogisticsMission` | redundant `= delete` copy declarations removed — their base classes (`Soldier`/`Vehicle`/`Mission`) already forbid copying, so repeating the deletion added nothing |

**Kept deliberately** (still needed):

| Class | What stays | Why |
|-------|-----------|-----|
| `MilitarySystem`, `BaseFacility`, `Warehouse` | destructor + deleted copy | They **own** the objects behind their pointer vectors (`delete` them in the destructor); shallow copies would double-delete |
| `Soldier`, `Unit`, `Vehicle`, `Mission` | deleted copy | Identity classes: unique ids, back-pointers (`Soldier↔Unit`), a non-reseatable `Unit&` reference member in `Mission` |
| `LinkedList` | destructor + deleted copy | Owns its heap-allocated nodes |

## Requirement ו — Singleton managing class

`MilitarySystem` constructor is now **private**; the only way to reach the system is:

```cpp
MilitarySystem& militarySystem = MilitarySystem::getInstance();
```

Implemented as a Meyers singleton (function-local `static` in `getInstance()`):
constructed lazily on first use, destroyed automatically at program exit, no dynamic
allocation, and copy construction/assignment remain deleted. `main` holds a
reference obtained once from `getInstance()`.

## Requirement ז — two additional design patterns

**1. Factory — `src/VehicleFactory.h/.cpp` (new files).**
`VehicleFactory::create(eVehicleType, vehicleNumber, maxPassengers, maxWeightKG)`
is now the single place in the program that says `new Jeep` / `new Truck` /
`new ArmoredTransport`. It replaced three nearly identical
`addJeep`/`addTruck`/`addArmoredTransport` methods in `BaseFacility` **and** their
three delegation twins in `MilitarySystem` — six methods collapsed into one
`addVehicle(type, ...)` in each class. `main` selects a `VehicleFactory::eVehicleType`
from the menu and makes one call.

**2. Observer — `src/MissionObserver.h` (new file) + changes in `Mission`.**
`Mission` keeps a vector of non-owning `MissionObserver*` subscribers
(`attach`/`detach`) and notifies them from `setStatus()` whenever the status
actually changes. The concrete observer, `ConsoleMissionNotifier`, is defined in
`main.cpp` — deliberately in the UI layer, so model classes make no presentation
decisions — and is attached by `MilitarySystem` to every mission it creates
(`setMissionObserver`). Updating a mission status now prints, e.g.:

```
[NOTIFICATION] Mission 'Supply' (ID 2) is now IN_PROGRESS.
```

**3. (Bonus) Iterator** — `LinkedList<T>::ConstIterator`, described under requirement א.

(Singleton from requirement ו is a third GoF pattern on top of these.)

## Other changes made along the way

- **`const_cast` cleanup in `MilitarySystem`** — Part 2 code called the public const
  finders and const_cast away the result in eight places. There are now private
  non-const lookups (`findSoldierMutable`, `findUnitMutable`, `findWarehouseMutable`)
  used by mutating operations; the public const finders remain for read-only callers.
  (Two documented const_casts remain where `BaseFacility` deliberately exposes only
  const getters to outsiders while its owner needs mutable access.)
- **`missionStatusName` duplication removed** — the same switch existed in both
  `TrainingMission.cpp` and `LogisticsMission.cpp`; it is now a single public static
  `Mission::statusName()`, also reused by the console notifier.
- **`addSoldier`/`addOfficer` duplication reduced** — shared validation extracted to
  a private `isValidPersonInput()` helper; mission storage + observer attachment
  shared via a private `storeMission()` helper.
- **`main.cpp`** — all `char buffer[256]` inputs replaced by `std::string` via a
  small `readWord()` helper (`LINE_LEN` deleted); menu option 14 added; vehicle
  creation switched to the factory enum. The Part 2 input-validation helpers
  (`readInt`, `readIntInRange`, `readDouble`) are unchanged.
- **Menu option 15 — mock data** — `createMockData()` builds a full demo scenario
  in one step (6 personnel, 2 units, assignments, an officer's command, all three
  vehicle types, a stocked warehouse, both mission types with vehicle/equipment,
  a driver, and a status change that fires the observer). Generated ids are derived
  from the current entity counts; names get a batch suffix so the option can be
  used repeatedly. See `MANUAL_TESTS.md` for guided test scenarios.
- **Project files** — `MilitarySystem.vcxproj` and `.filters`: removed `Utils.h`,
  added `LinkedList.h`, `MissionObserver.h`, `VehicleFactory.h`, `VehicleFactory.cpp`.

## Files added / removed

| Action | File |
|--------|------|
| Added | `src/LinkedList.h`, `src/MissionObserver.h`, `src/VehicleFactory.h`, `src/VehicleFactory.cpp`, `PART3_CHANGES.md`, `MANUAL_TESTS.md` |
| Removed | `src/Utils.h` |
| Modified | every other `.h`/`.cpp` in `src/`, `MilitarySystem.vcxproj`, `MilitarySystem.vcxproj.filters` |

## Verification

- **Build**: compiles and links with **zero warnings** (MSVC `/W3`, C++20, Debug x64).
- **LinkedList unit test**: a standalone test (compiled at `/W4`) covering add,
  remove of head/middle/tail, remove of the last element (tail-pointer reset),
  remove of a missing element, `print`, `isEmpty`, reuse after emptying, and
  iterator traversal — all assertions pass.
- **Full regression through the menu**: soldier + officer + assign-to-officer (14) +
  unit + transfer + Jeep/Truck/ArmoredTransport via the factory + warehouse +
  equipment + training mission + logistics mission with vehicle & equipment +
  status update (observer notification printed) + maintenance + print-all + report.
  All operations succeed and the final snapshot/report are correct.
- **Edge cases**: non-numeric input at the menu and at numeric prompts (recovers and
  re-prompts), out-of-range rank (rejected), Jeep with 0 passengers (clean error via
  exception, program continues), duplicate vehicle number (rejected), assigning a
  non-officer as a commander (rejected via `dynamic_cast` check).

## Notes for the submission

- The Part 3 zip must be **cleaned** before upload (course instructions): run
  Build → Clean Solution, then delete the hidden `.vs\` folder and both `x64\`
  output folders. The zip should be tens of KB.
- `main.cpp` intentionally keeps `readInt`-style helpers and all I/O — input and
  output stay out of the model classes (course checklist).
