# Manual Test Guide

Step-by-step scenarios to demonstrate and verify the system from the menu.
Start every session with a fresh run of the program unless a scenario says otherwise.

**Tip:** menu option **15 (Create mock data)** builds a full demo scenario in one
step and prints the ids it created — useful before testing operations that need
existing data. It can be run more than once (names get a `-M1`, `-M2`... suffix).

---

## 1. Smoke test (2 minutes)

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `15` | "Mock data ready" + a `[NOTIFICATION] Mission 'Drill-M1' ... IN_PROGRESS` line (the **Observer** fired during setup) |
| 2 | `12` | Full snapshot: 6 personnel (Gadi commands Avi+Ben — that block is printed from the **LinkedList**), 2 units, 3 vehicles (one of each type — created by the **Factory**), stocked warehouse, 2 missions (drill IN_PROGRESS, supply with truck + 2 equipment items) |
| 3 | `13` | Report: 6 soldiers, 2 units, 3 vehicles, 3 equipment items, 2 active missions |
| 4 | `0` | "Goodbye." — clean exit, no crash |

## 2. Personnel and units

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `1`, name `Yossi`, date `15 2 2000`, role `Cook`, rank `1` | "Soldier added." (personal numbers start at 100000 and are printed by option 12) |
| 2 | `2`, name `Rina`, date `1 1 1990`, role `Commander`, rank `4` | "Officer added." |
| 3 | `3`, name `Delta` | "Unit created." (unit ids start at 100) |
| 4 | `4`, Yossi's personal number, Delta's unit id | "Soldier assigned to unit." |
| 5 | `4` again, same soldier, same unit | "Failed..." — transferring to the unit he is already in is rejected |
| 6 | `3`, name `Echo`, then `4`, Yossi → Echo's id | "Soldier assigned to unit." — and option `12` shows he **left Delta** (no double membership) |
| 7 | `4` with personal number `999999` | "Failed..." — unknown soldier |

## 3. Officer's command (the linked list)

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `14`, officer = Rina's number, soldier = Yossi's number | "Soldier assigned to officer's command." |
| 2 | `14`, same pair again | "Failed..." — duplicates rejected |
| 3 | `14`, officer = **Yossi's** number (not an officer) | "Failed..." — the `dynamic_cast` check refuses a plain soldier as commander |
| 4 | `14`, officer = Rina, soldier = Rina | "Failed..." — an officer cannot command herself |
| 5 | `12` | Rina's entry shows "commands 1 soldier(s)" and lists Yossi |

## 4. Vehicles (factory) and maintenance

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `5`, type `1` (Jeep), number `J-77`, passengers `4` | "Vehicle added." |
| 2 | `5`, type `1`, number `J-77` again | "Failed to add vehicle." — duplicate vehicle number |
| 3 | `5`, type `1`, number `J-78`, passengers `0` | "Error: Jeep: maxPassengers must be >= 1" — constructor threw, **program keeps running** |
| 4 | `5`, type `2` (Truck), number `T-77`, weight `-5` | "Error: Truck: maxWeightKG must be positive" |
| 5 | `5`, type `3`, number `A-77`, passengers `6`, weight `900` | "Vehicle added." — ArmoredTransport combines both parameter sets (multiple inheritance) |
| 6 | `11`, number `J-77` | "Vehicle marked for maintenance." — option `12` now shows it "unavailable (needs maintenance)" |
| 7 | `11`, number `NOPE` | "Vehicle not found." |

## 5. Warehouse and equipment

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `6`, name `Depot1` | "Warehouse added." |
| 2 | `6`, name `Depot1` again | "Failed..." — duplicate warehouse name |
| 3 | `7`, warehouse `Depot1`, equipment `Radio`, S/N `SN9`, qty `5`, status `0` | "Equipment added." |
| 4 | `7`, warehouse `Nowhere` | "Warehouse not found." |
| 5 | `7`, ..., qty `-3` | "Failed to add equipment." (negative quantity rejected) |

## 6. Missions and the observer

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | `8`, name `NightDrill`, an existing unit id, type `2`, difficulty `2` | "Training mission created." |
| 2 | `8` with unit id `999` | "Failed..." — unknown unit |
| 3 | `9`, name `Resupply`, existing unit id, vehicle `y` → pick an existing number, equipment `y` → existing warehouse + `Radio`, then `n` | Mission created with vehicle and equipment attached (verify with `12`) |
| 4 | `10`, the mission's id, status `1` | **`[NOTIFICATION] Mission '...' is now IN_PROGRESS.`** followed by "Status updated." — the Observer pattern in action |
| 5 | `10`, same mission, same status `1` | "Status updated." but **no notification** — observers are only notified on an actual change |
| 6 | `10`, status `2` (COMPLETED), then `13` | Notification fires; the report's "Missions (not completed)" count drops by 1 |

## 7. Input robustness (Part 2 fixes, still holding)

| Step | Action | Expected result |
|------|--------|-----------------|
| 1 | Type `abc` at the main menu | "Invalid input, please enter a number." and the prompt returns — no exit, no infinite loop |
| 2 | `1`, then type `xx` for Day | Error + re-prompt for Day; entering valid values afterwards completes normally |
| 3 | `1`, ..., rank `9` | "Value must be between 0 and 5." + re-prompt |
| 4 | `1`, date `31 2 2001` | "Failed to add soldier." — invalid calendar date (Feb 31) |
| 5 | `5`, type `7` | "Value must be between 1 and 3." + re-prompt |

## 8. Singleton sanity (code-level, not menu)

There is no way to create a second `MilitarySystem`: the constructor is private and
copying is deleted. `MilitarySystem ms;` or `auto copy = MilitarySystem::getInstance();`
anywhere in the code produces a **compile error** — only
`MilitarySystem& ms = MilitarySystem::getInstance();` works.
