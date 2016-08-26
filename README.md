BT Utility Plugin
-------------
An extension to the UE4 behavior tree adding support for utility-based selection.

This is a stripped down version of an in-progress engine mod (https://github.com/kamrann/UnrealEngine) which omits some editor modifications, but maintains the core functionality as a plugin which can work with a regular engine installation.

NOTES
-------------
In order to keep as much in line as possible with existing behavior tree/decorator behavior, the UtilitySelector node works essentially as a regular Selector node but with dynamically determined ordering of children.
This ordering is calculated each time the UtilitySelector is activated, and then remains fixed.

For priority selection, on activation the child utility values will be evaluated and then the children ordered by decreasing utility value.
For proportional selection, on activation an ordering is determined such that children with higher utility values are more likely to be earlier in the ordering (The chance of a child being first is directly proportional to its utility value; the process is then repeated for the remaining children with the first one removed from consideration, until all children are in the ordering).

Once the ordering is determined, the node excutes as a regular selector, trying children in order until one succeeds.

Note that custom blueprint based utility functions do not currently expose the usual decorator events such as activation/tick. This is partly due to it requiring either copying a large amount of code from the UBTDecorator_BlueprintBase class, or adding performance overhead by using an interface. However, due to the above way in which utility functions are only evaluated once when the UtilitySelector is activated, it is also not obvious to me that these events are useful for utility functions. If anyone finds they do require them, please get in touch.
