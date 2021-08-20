1. Before using this example, add **FREERTOS_KERNEL_PATH** variable into .bashrc file, located in your home directory 

    For example:

    **$ gedit ~/.bashrc**

        export FREERTOS_KERNEL_PATH=/home/petro/cxemotexnika/Examples/FreeRTOS-Kernel

    **$ source ~/.bashrc**

2. Download Git Submodules

    **$ git submodule init**

    **$ git submodule update**

    or

    **$ git clone --recurse-submodules https://github.com/PetroShevchenko/cxemotexnika.git**

3. Switch main branch of FreeRTOS-Kernel to smp branch, if you want to use both Cortex-M0+ cores for FreeRTOS

    **$ cd ~/cxemotexnika/Examples/FreeRTOS-Kernel**

    **$ git checkout smp**

4. Build the example

    **$ cd ~/cxemotexnika/Examples/Raspberry-Pi-Pico/FreeRTOS_Demo**

    **$ ./pico.sh build**

5. Upgrade the firmware

    **$ ./pico.sh upgrade**

6. Connect picoprobe and launch minicom

    **$ ./pico.sh monitor**



