Repo for Milrem Summer School application.

Code is for https://www.codingame.com/ide/puzzle/mad-pod-racing challenge. This code got me promoted to gold league.

**Target Offset**

The aim of applyng an offset is to make the pod steer more aggressively - not just aim for the centre of the CP, but that area in general. The idea is to apply a vector proportional to the "impulse vector" of the pod to the checkpoint (CP). This makes the target position of the pod move "towards" the pod.

The impulse vector is calculated using p = (current_position - last-posistion). The vector is then multiplied by a parameter which governs the amplitude of the correction. The parameter was arbitarily chosen as h=2 and it worked to a desired degree. The adjusted target is gives as target = Checkpoint_coordinates - p*h. 

A visualisation is given below.

![alt text](https://github.com/kuubikus/Pod_Racing/blob/main/for_readme.jpg)

**Further work**
- Create a class for pod to enable control of two pods in gold league
- Develop and test tactics with two pods. Idea is to have one racer pod and one interceptor. The goal of the interceptor is to disturb the other team with a main goal of pushing the opponent to the last position.
- Make use of shield and collision tactics
