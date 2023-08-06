# Goldstone Introduction

Goldstone is a reference open-source Network Operating System (NOS) for disaggregated open optical networking hardware. Goldstone is developed as part of Telcom-infra-project’s [OOPT-NOS (Open Optical and Packet Transport)](https://telecominfraproject.com/oopt/) software project group. It is mainly aimed at accelerating the adoption of disaggregated networking optical systems.

Several open-source components developed as part of [OCP(Open Compute Project)](https://www.opencompute.org/projects/networking), [TIP(Telcom Infra project)](https://telecominfraproject.com/oopt/) and [ONL(Open Network Linux)](http://opennetlinux.org/) are used as the basic building blocks of Goldstone NOS.
1. ONL &emsp; &ensp; &ensp; &nbsp;: ONL is used as base operating system, which has support for wide range of open network devices.
2. SAI &emsp; &ensp; &ensp; &ensp; : Abstraction layer to control/Manage forwarding ASICs/NPUs. 
3. SONIC &emsp; &ensp; : To provision switching and routing support for networking platforms.
4. TAI &emsp; &ensp; &ensp; &ensp; : Abstraction layer to control/Manage coherent optical Hardware components.
5. Docker &emsp; &nbsp; : Simplifies the process of building, running, managing, and distributing applications.
6. Kubernetes : Enables containerized application management.

# System-Design

![image](https://user-images.githubusercontent.com/36222193/161417226-5466d422-493b-423f-ac89-8b1f2e0333cc.png)

This modular architecture brings in the ease of assimilating new technologies and feature-advancements of open-source projects mentioned above into Goldstone-NOS. And also enables Goldstone to extend its support for other networking devices [L0/L1 Transponders, ROADMs.. etc.] in future.

### _Unified Management Layer_
The unified management layer provides a common APIs towards different north bound management protocols like CLI, netconf, restconf, gNMI SNMP etc.

![image](https://user-images.githubusercontent.com/36222193/161416077-02cb0a25-53ed-4222-9328-7cc5906bd723.png)

Goldstone uses 'Sysrepo', a library for configuration and monitoring based on the YANG model as a core component of the management layer.
Unified-management-layer's architecture is such that each component that caters to the northbound API is an independent process and does not require changes to existing parts when adding a new northbound API.

### _ONL & ONLP_
Open Network Linux (ONL) is an open-source, foundational platform software layer for next-generation, modular NOS architecture on open networking hardware.

More information <[here](http://opennetlinux.org/)>.

The Open Network Linux Platform (ONLP) APIs provide a common, consistent abstraction interface for accessing important platform assets such as SFPs, PSUs, Fans, Thermals, LEDs, and ONIE TLV storage devices.

More information <[here](https://opencomputeproject.github.io/OpenNetworkLinux/onlp/)>.

### _TAI [Transponder Abstraction Interface]_
Transponder Abstraction Interface [TAI], defines API’s to provide a vendor independent way of programming the transponders from various vendors. 
TAI acts as hardware abstraction interface between the system software (NOS) and the coherent optical devices. There by allowing all the TAI complaint transponders to operate with any system software having TAI layer integrated.

![image](https://user-images.githubusercontent.com/36222193/161417073-41f8cd78-a227-4bae-a300-aca49e4b4c2e.png)

More information <[here](https://github.com/Telecominfraproject/oopt-tai)>.

### _SONIC & SAI_
SONiC is an open source network operating system based on Linux that runs on switches from multiple vendors and ASICs. SONiC offers a full-suite of network functionality, like BGP and other L2 & L3 protocols.

More information <[here](https://azure.github.io/SONiC/)>.

The Switch Abstraction Interface defines the API to provide a vendor-independent way of controlling forwarding elements, such as a switching ASIC, an NPU or a software switch in a uniform manner.

More information <[here](https://github.com/opencomputeproject/SAI/wiki)>.


