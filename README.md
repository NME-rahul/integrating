# integrating


## slots based

### Supervisory node:
* this will work based on queue structure.
* each device will do operation in a certain time quanta in which device can communicate with supervisor and read/write memory.

#### pros:
* easy to implement.
* each device will have it's own time so no device will conflict in read/write.

### Device side:
* each device will work on it's own slot.

#### cons:
* if the device has to read/wrire a large chunk of data and if it took more time then given time quanta then rea/write will stop in-between the operation.
* device has to wait for it's time slot and this leads to slow read/write speed.
* if a device has some data in it's buffer to read and waiting for slot and at the same time the device adds more data to read/write thus increase the size of buffer and increased size of leads to problem 1.
* A large size of buffer can send a device in infinite waiting time to read/write and by increasing time quanta value makes other device slow and may fall in the same condition of infinite wait(starvation).



## open when needed

### Supervisory Node:
* the supervisory node will sense each device repeatdly, is any one try to communcate?
* as any device start communication device pin(which is connencted to superviosr) pin will go in HIGH state.
* in supervisor, the rest of the pin will go in HIGH state to indicate the other device that is memory, is busy.


* if any device start communication, let device 3 start communication:
  
  |supervisor pin |       devices no     |       device pin    |
  |---------------|       ---------------|       ---------------|
  |HIGH           |       1              |       LOW            |
  |HIGH           |       2              |       LOW            |
  |LOW            |       3(starts)      |       HIGH           |
  |HIGH           |       4              |       LOW            |
  |.              |       .              |       .              |
  |.              |       .              |       .              |
  |.              |       .              |       .              |
  |HIGH           |       n              |       LOW            |

* else
  
  |supervisor pin |       devices no     |       device pin     |
  |---------------|       ---------------|       ---------------|
  |LOW            |       1              |       LOW            |
  |LOW            |       2              |       LOW            |
  |LOW            |       3              |       LOW            |
  |LOW            |       4              |       LOW            |
  |.              |       .              |       .              |
  |.              |       .              |       .              |
  |.              |       .              |       .              |
  |LOW            |       n              |       LOW            |


#### cons:
* if other device wants to communicate and the link is busy the device has to wait and continue it's own operation.
    * in this case the device can add it's data to buffer. multiple time of this increase the size of buffer and may leads the device in starvation state.
    * device can wait for certain amount of time and try to start communicating again. and this make it to slow in other operation.
* complex to implement.

#### solution:
* we can implement a queue in the devices so that it can sense link and do other operations, repeatdly.

## Input Based

* A device will be connected to the supervisory node with two lines.
  * 1: when supervisor has input for device, and it wants to wake the device for read/write.
  * 2: when the device wants to read/write.

**supervisor**
* Create a Local server(run in supervisor node), and use it as a input device while giving input through local server provide the name/number of the device for the for the input is.
* First store the input in storage device and then wake up(other node will stay in low state) the partiular device which is speicified in the input.
* we can wake up multiple device only if the input has no read/write operation.

**Device**
* A device will only wake up for read/write when it's name/number will be in the input otherwise it will work on instruction provided rigidly.
* If a device has to read/write it will sense the make it's node as HIGH(after it device has to wait for reply). if any node from device side is HIGH the supervisory node will check for business, if no other device is reading/writing then the supervisory node will send reply to grant permission for read/write.

#### Cons:-
* complexity of input comands.
* if a Device has to read/write at the same time when a node is HIGH then the device has to stop it's operation until it gets reply from supervisor node.


---

#### Why this slots will not work in "slot based" technique?
* beacuse the device is able to sense the link on it's slot and it can miss it's slot beacuse the devices not have same cpu clock speed. this condition can occur in "open when needed" technique but frequency is very low beacuse we are implemeting queue only in one side(device).
* we know device won't access much memory. 
* we can sync the all the device by time delay but in this way we will waste the computation power of higher speed devices.
