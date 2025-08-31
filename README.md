# steering_v2_0

## Description
The Steering system serves as an hub for all the controls that the driver can toggle during the driving. It is fundamental as it allows to change different settings such as Controls and Power

---

## Components

- **stm32f446**
    32-bit MCU based on ARM Cortex-M4, 512Kb of Flash and 128Kb of SRAM

- **5 Buttons**
    working with interrupts in falling mode and configured with pullup
    
- **3 Rotary Dip Switch**
    10 positions, already implementing digital signals to avoid using adc channel of the MCU

- **CAN Communication**
    to send the status of buttons and switches

## Buttons

1. **BTN_TC**: Traction control
2. **BTN_TV**: Torque vectoring
3. **BTN_LC**: Launch control
4. **BTN_RTD**: Ready to drive 
5. **BTN_USER**: Additional button

## Rotary Dip Switches

1. **RSW1**: Power regulation
2. **RSW2**: Control incidence
3. **RSW3**: Additional rotary