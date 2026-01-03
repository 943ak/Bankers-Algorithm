# Banker’s Algorithm – Deadlock Avoidance (C)

This project implements **Banker’s Algorithm** in C, a classic deadlock
avoidance algorithm used in operating systems to ensure safe resource
allocation.

The program models processes, resources, and system state, verifies
whether the system is in a safe state, and evaluates dynamic resource
requests.

---

## ✨ Features

- Calculation of the **Need Matrix**
- Safety algorithm to determine **safe / unsafe state**
- Generation of **safe execution sequence**
- Handling of **resource requests**
- Rollback on unsafe allocation
- Clear, step-by-step output

---

## 🛠️ Concepts Used

- Deadlock avoidance
- Resource allocation graphs
- Safety algorithm
- Need, Allocation, Max, Available matrices
- OS process-resource modeling
- Defensive allocation & rollback

---

## 📊 Algorithm Overview

1. Compute **Need = Max − Allocation**
2. Use the **Safety Algorithm** to determine system state
3. For resource requests:
   - Verify `Request ≤ Need`
   - Verify `Request ≤ Available`
   - Temporarily allocate resources
   - Re-run safety algorithm
   - Grant or rollback based on result

---

## 🚀 Build & Run

### Build
```bash
make

### Run
```bash
./P2
