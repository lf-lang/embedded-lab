# 10 Coordination of Distributed Cyber-Physical Systems
<!-- TODO: Update the introduction -->
The purpose of this exercise is to learn challenges in coordinating distributed nodes in cyber-physical systems, such as the [CAL theorem](https://doi.org/10.1145/3609119) defining the fudnamental tradeoff of consistency, availability, and latency in distributed systems. In this exercise, we are not using the Pololu robot.

### Prerequisites

---

1. The provided LF source files, Protocol Buffers file, and input images. To build and run the program directly on your laptop, you need `lfc-dev`, a C build environment, and a Python virtual environment with PyTorch and torchvision.
2. On Ubuntu/Debian Linux, you need `sudo` privileges and `iproute2` for the `tc` command. If `ping` is unavailable, install it with `sudo apt install iputils-ping`.
3. On an Apple Silicon Mac, install and start Docker Desktop. The provided `byeonggiljun/cse522-lab8:arm64` image includes the files and execution environment needed for this lab.
4. On x86-64 WSL, install Docker Desktop and enable WSL integration. The provided `byeonggiljun/cse522-lab8:amd64` image includes the files and execution environment needed for this lab.


## 10.1 Prelab

**Questions**
<!-- Read a section in the CAL theorem paper and ask a question -->
<!-- Question about Lag (give a link? https://www.lf-lang.org/docs/next/writing-reactors/time-and-timers/) -->
<!-- Pytorch toy example -->

<style type="text/css">
    ol ol { list-style-type: lower-alpha; }
</style>

1. Read the first seven paragraphs of the Introduction of the paper ["Consistency vs. Availability in Distributed Cyber-Physical Systems"](https://doi.org/10.1145/3609119).
    1. Consider a warehouse where multiple distributed robots work together. Since the aisles are narrow, the robots share information about aisle occupancy to avoid collisions or blocking each other. Therefore, it is important to ensure that all robots have the same view of the current aisle occupancy. Which of the following properties is most directly related to this requirement: **consistency, availability, or latency**? Briefly explain your answer.
    2. Consider a vehicle equipped with an advanced driver assistance system (ADAS), where both an autonomous vision-based system and the physical brake pedal can trigger the braking system. When either input source generates a braking request, it is important to actiavate brakes as quickly as possible. Which of the following properties is most directly related to this requirement: **consistency, availability, or latency**? Briefly explain your answer.
    3. The paper mentiones that network partitioning is a limiting case of network latency. How could we express the network partitioning using the network latency? Specifically, consider two distributed nodes where the network latency is $l$. What would be the value of $l$ if the network is partitioned?
2. In Lingua Franca, the term **lag** is defined as physical time minus logical time ([LF Handbook - time and timers](https://www.lf-lang.org/docs/next/writing-reactors/time-and-timers/)). For instance, if a reaction is executed at physical time $106\,ms$, where the scheduled logical time is $100\,ms$, the lag is $6\,ms$.
    1. **True or False**: In general, a larger lag corresponds to lower availability. Briefly explain your answer. **Hint** You can refer to Section 4.2 in the [CAL theorem](https://doi.org/10.1145/3609119) paper.
    2. Can a lag become negative in Lingua Franca under the default execution semantics of reactor model? Briefly explain your answer.
3. Extracting values from PyTorch tensors. A pretrained object detection model returns a dictionary containing three tensors: `prediction["labels"]` contains object category IDs, `prediction["scores"]` contains confidence scores, and `prediction["boxes"]` contains bounding boxes in the form `[x1, y1, x2, y2]`. The following loop examines one detection at a time:

    ```python
    for label, score_tensor, box_tensor in zip(
        prediction["labels"], prediction["scores"], prediction["boxes"]
    ):
        # Examine this detection.
        pass
    ```

    1. Here, `label` and `score_tensor` are zero-dimensional tensors. Write Python expressions that extract the label as an integer and the confidence score as a floating-point number. How would you check whether the label is `1`, the COCO category ID for a person?
    2. `box_tensor` contains four coordinates. Write Python code that extracts these coordinates into `x1`, `y1`, `x2`, and `y2`. Which expression gives the horizontal center of the bounding box?

    **Hint:** Review the PyTorch tensor methods `.item()` and `.tolist()`.

## 10.3 ADAS Example

In this exercise, you will complete a pedestrian detector for an advanced driver assistance system (ADAS). Copy the provided [ADASPolyglotTemplate.lf](./ADASPolyglotTemplate.lf) to `src/ADASPolyglotSolution.lf`. Keep [ProtoAdas.proto](./ProtoAdas.proto) in `src/` and the supplied images in the repository's `data/` directory. Run the program from the repository root so that the camera can find the images.

This program is a **polyglot federation**, a collection of federates implemented in different target languages. The `Vision` federate uses Python for image processing, while the `Braking` federate uses C for the brake pedal and brake reactions. The `@language` annotations specify their languages, and the `"proto"` serializer lets them exchange Protocol Buffers messages. Read the [LF Handbook section on Polyglot Federations](https://www.lf-lang.org/docs/writing-reactors/polyglot/) for more information.

First, examine and run the template. The `Camera` reactor reads the images in numeric order and repeatedly sends them on a timer with a period of 30 ms. `PedestrianDetector` loads a pretrained torchvision Faster R-CNN model and runs inference on each frame. However, the unfinished condition skips every detection, so the template reports no pedestrian hazard and sends no automatic brake requests. `BrakePedal` schedules one manual brake event at startup. The actual reaction times and any deadline violations depend on coordination and computation delays; the 30 ms timer period does not guarantee that inference finishes within 30 ms.

Your task is to complete the TODOs in `PedestrianDetector`. A detection should trigger an automatic brake request only if all of the following conditions hold:

1. The object has COCO category ID `1` (person).
2. Its confidence score is at least `0.90`.
3. The horizontal center of its bounding box is between 30% and 70% of the image width, inclusive. This region represents the road area for this exercise.

Set `hazard` to `True` and break out of the loop when you find a qualifying detection. The provided code then sends a `ProtoAdas` message to `Braking`. Do not add a bounding-box area condition.

**Hint:** Use your answers to prelab question 3 to extract the tensor values. Divide the horizontal center coordinate by `image_width` to compare it with the road region boundaries.

**Checkoff:** Show one complete image cycle in which only `image_10.png` is identified as a pedestrian hazard. Show that the resulting automatic brake message reaches the C `Braking` federate. If a deadline violation occurs, explain how you can distinguish message reception from completion of the normal brake reaction.

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

Run your completed program with the baseline network conditions, then use Linux's `tc` command to add network delay. Keep the model, camera timer, coordination settings, and connection's `after` value fixed so that you can compare the effect of network latency on lag.

On Ubuntu/Debian Linux, install `iproute2`:

```sh
sudo apt update
sudo apt install iproute2
```

On an Apple Silicon Mac, start Docker Desktop and run these commands in the host terminal:

```sh
docker pull byeonggiljun/cse522-lab8:arm64

docker run -it \
    --name cse522-lab8 \
    --cap-add=NET_ADMIN \
    byeonggiljun/cse522-lab8:arm64 \
    bash
```

The image contains the required lab files and execution environment. The `NET_ADMIN` capability allows you to configure network delay inside the container.

For x86-64 WSL, use the following commands once the `amd64` image is published. This image is not yet available.

<!-- TODO: Publish byeonggiljun/cse522-lab8:amd64 before enabling the WSL instructions. -->

```sh
docker pull byeonggiljun/cse522-lab8:amd64

docker run -it \
    --name cse522-lab8 \
    --cap-add=NET_ADMIN \
    byeonggiljun/cse522-lab8:amd64 \
    bash
```

If you have already created and exited the container, reconnect with `docker start -ai cse522-lab8` rather than creating another container with the same name.

Run the RTI and both federates in the same Linux environment or the same container for this experiment. First, run `ping localhost` and your completed ADAS program without added delay to record the baseline RTT, lag, and deadline behavior. Press `Ctrl+C` to stop `ping`.

Next, run these commands on Linux or inside the container to add 100 ms of delay to packets sent through the loopback interface, `lo`:

```sh
sudo tc qdisc add dev lo root netem delay 100ms
ping localhost
```

**Hint:** If you are running as root inside the container, omit `sudo`. If `add` fails because a root queue discipline already exists, inspect it with `tc qdisc show dev lo`. Remove it with the cleanup command below only if it is a setting you added for this experiment, then try again.

The delay applies to all loopback traffic, including communication with the RTI, not just messages between `Vision` and `Braking`. Ping measures round-trip time (RTT): both the request and the reply are delayed, so the measured RTT may increase by approximately 200 ms rather than 100 ms. Press `Ctrl+C` to stop `ping`, then run your completed ADAS program in the same environment and compare its lag and deadline behavior with the baseline.

After the experiment, remove the added delay and run `ping localhost` again to verify that the RTT returns to its baseline:

```sh
sudo tc qdisc del dev lo root
ping localhost
```

**Note:** The `after` clause adds a delay to the logical timestamp of a message. Changing it does not inject actual network latency. For this experiment, change the network delivery delay rather than the `after` clause.

**Checkoff:** Show results (including the measured lags) for the baseline and the 100 ms added-delay condition. Explain how the results relate to availability.

## 10.5 Federated Execution

Now run `Vision` and `Braking` on separate devices. Work with another student and connect both laptops to the same Wi-Fi network. One laptop will run the runtime infrastructure (RTI) and `Braking`; the other will run `Vision`.

Docker is not required for this section. We recommend running the programs directly on each laptop with the necessary build and Python environments installed. If you use Docker, container addresses may differ from host addresses, and additional port forwarding, IP address configuration, or routing may be needed to communicate between laptops. The loopback delay configured in Section 10.4 does not apply to Wi-Fi traffic between the two laptops.

The template declares `federated reactor at localhost`. Here, `localhost` refers to the computer running the program. The generated launcher runs the RTI and both federates on that computer. To connect two laptops, first run `ifconfig` on the RTI laptop and find the IPv4 address of its Wi-Fi interface. Use that address in the `federated reactor` declaration on both laptops. For example:

```lf
federated reactor at 192.168.0.1 {
    braking = new Braking()
    vision = new Vision()

    vision.trigger_brake -> braking.brake_assistant after 10 msec serializer "proto"
}
```

Replace the example address with the RTI laptop's actual address and retain your existing connection delay and other settings. This declaration specifies the RTI's location. You will choose where each federate runs by starting its generated program separately.

On each laptop, activate the Python virtual environment and compile the same `src/ADASPolyglotSolution.lf` using `lfc-dev`. Each laptop must compile its own executables. The Vision laptop also needs the supplied `data/` directory and the pretrained model dependencies. Run all commands below from the repository root.

First, start the RTI on the chosen laptop:

```sh
fed-gen/ADASPolyglotSolution/bin/RTI -n 2 -i adas-lab
```

The `-n 2` option tells the RTI to expect two federates. In another terminal on the same laptop, start `Braking`:

```sh
fed-gen/ADASPolyglotSolution/bin/federate__braking -i adas-lab
```

On the other laptop, activate the Python virtual environment and start `Vision`:

```sh
fed-gen/ADASPolyglotSolution/bin/federate__vision -i adas-lab
```

All three programs must use the same federation ID, here `adas-lab`. For this experiment, start the programs individually rather than using the launcher that starts both federates together.

**Checkoff:** Show the execution results from both laptops. Demonstrate that `Vision` detects the pedestrian and sends an automatic brake request that is received by `Braking` on the other laptop.


## 10.6 Postlab Questions
1. Considier a vehicle with ADAS (advanced driver assistance systems) that triggers the brake automatically in an emergency. Which should be more important, strong consistency or high availability? Why?

2. In 10.3, we detect the pedestrian by checking only the center of the bounding box. Suppose we want to make the system triggers a brake only if a pedestrian is close enough. Which condition would you add to the current system to achive this goal?
  
3. What were your takeaways from the lab? What did you learn during the lab? Did any results in the lab surprise you?
