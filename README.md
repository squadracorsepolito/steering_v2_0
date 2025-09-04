# steering_v2_0

## Description
The Steering system serves as an hub for all the controls that the driver can toggle during the driving. It is fundamental as it allows to change different settings such as Controls and Power


## Components

- **stm32f446**
    32-bit MCU based on ARM Cortex-M4, 512Kb of Flash and 128Kb of SRAM

- **5 Buttons**
    working with interrupts in falling mode and configured with pullup
    
- **3 Rotary Dip Switch**
    10 positions, already implementing digital signals to avoid using adc channel of the MCU

- **CAN Communication**
    to send the status of buttons and switches


## Modules

### 1. steering 
#### Inc/steering.h Src/steering.c 
contains the function to be run in the main, it call the sample of buttons and switches and send CAN messages. 

```c
void steering_run(btnStateHandleTypedef *hbtn, rswStateHandleTypedef *hrsw);
```

### 2. IIR_filter
#### Inc/IIR_filter.h Src/IIR_filter.c
starting from an analog filter define the structure and implements a low pass IIR filter of the first order. Used to sample and debounce buttons and rotary DIP switches.

```c
typedef struct {
    float alpha;        //alpha = RC/(Ts + RC)
    float out;
} IIR_filter; 

void IIR_Init(IIR_filter *filter, float alpha);
float IIR_Update(IIR_filter *filter, float in);
```

some math:
```m
% first-order IIR recursive difference equation:
y(n) = (1 - alpha) * x(n) + alpha * y(n-1)                          % where 0 <= alpha <= 1   

% from the differential equation of a LP filter and discretization:                                     
Vout(n) = (Ts / (Ts + RC)) * Vin(n) + (RC / (Ts + RC)) * Vout(n-1)  % (RC / (Ts + RC)) = alpha
```

### 3. buttons
#### Inc/buttons.h Src/buttons.c
handle the buttons and define the functions for sampling their state.
- **BTN_1**: Traction control
- **BTN_2**: Torque vectoring
- **BTN_3**: Launch control
- **BTN_4**: Ready to drive 
- **BTN_5**: Additional button

```c
typedef struct {
    uint8_t state[5];
    uint8_t prev_state[5];
    uint8_t active[5];
    IIR_filter filter[5];
} btnStateHandleTypedef;

void BTN_Init(btnStateHandleTypedef *hbtn);
void BTN_Sample(btnStateHandleTypedef *hbtn);
```

### 4. rotary_switch
#### Inc/rotary_switch.h Src/rotary_switch.c
handle the 3 rotary DIP switches and define the functions for sample their position.
- **RSW1**: Power regulation
- **RSW2**: Control incidence
- **RSW3**: Additional rotary

```c
typedef struct {
    GPIO_TypeDef *gpiox[4];
    uint16_t pin[4];
    uint8_t state[4];
    IIR_filter filter[4];
    uint8_t position;
} RSW_t;

typedef struct {
    RSW_t power;
    RSW_t control;
    RSW_t user;
} rswStateHandleTypedef;

void RSW_Init(rswStateHandleTypedef *hrsw);
void RSW_sample_one(RSW_t *rsw);
void RSW_sample(rswStateHandleTypedef *hrsw);
```

### 5. can
#### Inc/can.h Src/can.c
Implements all the function needed for the CAN transmission.

```c
void CAN_build_payload(uint8_t *payload, btnStateHandleTypedef *hbtn, rswStateHandleTypedef *hrsw);
void CAN_steering_Msg_send(CAN_HandleTypeDef *hcan, uint8_t *buffer, uint8_t len);
 ```
