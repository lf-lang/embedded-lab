# 10 Coordination of Distributed Cyber-Physical Systems
<!-- TODO: Update the introduction -->
The purpose of this exercise is to have you familiarized with the CAL theorem defining the fudnamental tradeoff of consistency, availability, and latency in distributed systems. In this exercise, we are not using the pololu robot.

### The CAL Theorem

[**Lee et al. (2023)**](https://doi.org/10.1145/3609119) proved the following result for distributed cyber-physical systems:

> **CAL Theorem:** It is impossible to achieve consistency without paying a price in availability. The minimum price is proportional to the latencies in the system: network communication latency, computation overhead, and clock synchronization error.

This is a strengthening of the famous **CAP theorem** (Brewer, 2000), which says you cannot have all three of: Consistency, Availability, and Partition-tolerance. The CAL theorem goes further: even in a system with *no* partitions, apparent latency, including network delay, computation overhead, and clock synchronization error, introduces an unavoidable tradeoff.

For our grid:

| Term | Meaning |
|------|---------|
| **Consistency** | Both control nodes agree on the grid balance at every logical timestamp |
| **Availability** | How quickly an operator's command takes effect (low wait = high availability) |
| **Latency** | Network round-trip time + clock sync error + computation overhead |

The CAL theorem says that strong consistency requires enough waiting, or enough tolerated inconsistency, to cover apparent latency. There is no shortcut.

---

### Prerequisites
1. Install the RTI
2. Linux: tc command, Mac: Toxyproxy?
2. Pytorch?


## 10.1 Prelab

**Questions**

1. Considier connected autonomous vehicles at an intersection. Which should be more important, strong consistency or high availability? Why?
2. Considier a vehicle with ADAS (advanced driver assistance systems) that triggers the brake automatically in an emergency. Which should be more important, strong consistency or high availability? Why?
3. 

## 10.2 Federated Execution

**Checkoff:** Show the screenshots of the execution result from two physically separated devices.
## 10.3 ADAS Example
<!-- Give the link of the file (ADAS.lf) and let students download and add the file to the repo by creating a directory -->
<!-- Programming exercise: implement pedestrian detector (give the video and let ML model detect human) -->
<!-- Polyglot federation (Vision is python-target and Brake is C-target) -->
**Checkoff:** Show your output of `ADAS.lf` - image detection.
## 10.4 Consistency vs. Availability

**Checkoff:** With the round-trip time (RTT) of 10 ms, show the program experiencing low availability.


## 3.6 Postlab Questions

1.
  
2.

3. 
