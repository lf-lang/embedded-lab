# 10 Coordination of Distributed Cyber-Physical Systems
<!-- TODO: Update the introduction -->
The purpose of this exercise is to learn challenges in coordinating distributed nodes in cyber-physical systems, such as the [CAL theorem](https://doi.org/10.1145/3609119) defining the fudnamental tradeoff of consistency, availability, and latency in distributed systems. In this exercise, we are not using the pololu robot.

### Prerequisites
---
1. Install the RTI <!-- TODO: Give the link instead of giving the whole instructions --> <!-- TODO: Ask Prof. Lee about the location of the RTI installation instructions in the handbook -->
2. Linux: tc command, Mac: Toxyproxy?
2. Pytorch?


## 10.1 Prelab

**Questions**
<!-- Read a section in the CAL theorem paper and ask a question -->
<!-- Question about Lag (give a link? https://www.lf-lang.org/docs/next/writing-reactors/time-and-timers/) -->
<!-- Pytorch toy example -->
1. 
2. 
3. 

## 10.3 ADAS Example
<!-- Give the link of the file (ADAS.lf) and let students download and add the file to the repo by creating a directory -->
<!-- Programming exercise: implement pedestrian detector (give the video and let ML model detect human) -->
<!-- Polyglot federation (Vision is python-target and Brake is C-target) -->
<!-- Other datasets? -->
<!-- Report the type issue after finding the minimal program giving the same error. -->
**Checkoff:** Show your output of `ADAS.lf` - image detection.

## 10.4 The CAL Theorem

[**Lee et al. (2023)**](https://doi.org/10.1145/3609119) proved the following result for distributed cyber-physical systems:

> **CAL Theorem:** It is impossible to achieve consistency without paying a price in availability. The minimum price is proportional to the latencies in the system: network communication latency, computation overhead, and clock synchronization error.

This is a strengthening of the famous **CAP theorem** (Brewer, 2000), which says you cannot have all three of: Consistency, Availability, and Partition-tolerance. The CAL theorem goes further: even in a system with *no* partitions, apparent latency, including network delay, computation overhead, and clock synchronization error, introduces an unavoidable tradeoff.

For our ADAS example:
| Term | Meaning |
|------|---------|
| **Consistency** | Both brake control nodes (remote and local) agree on the brake result at every logical timestamp |
| **Availability** | How quickly an operator's command takes effect (low wait = high availability) |
| **Latency** | Network round-trip time + clock sync error + computation overhead |

The CAL theorem says that strong consistency requires enough waiting, or enough tolerated inconsistency, to cover apparent latency. There is no shortcut.

**Checkoff:** With the round-trip time (RTT) of 10 ms, show the program experiencing low availability.

## 10.5 Federated Execution

**Checkoff:** Show the screenshots of the execution result from two physically separated devices.


## 10.6 Postlab Questions
1. Considier connected autonomous vehicles at an intersection. Which should be more important, strong consistency or high availability? Why?
2. Considier a vehicle with ADAS (advanced driver assistance systems) that triggers the brake automatically in an emergency. Which should be more important, strong consistency or high availability? Why?
  
3. 
