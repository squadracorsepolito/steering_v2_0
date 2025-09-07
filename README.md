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
typedef struct {
    BTN_handleTypedef hbtn[BTN_Device_NUM];
    RSW_handleTypedef hrsw[RSW_Device_NUM];
} Steering_Board;

void Steering_Init(void);
void Steering_Run(void);
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
#### Inc/bsp.h Src/bsp.c
handle the buttons and define the functions for sampling their state.
- **BTN_1**: Traction control
- **BTN_2**: Torque vectoring
- **BTN_3**: Launch control
- **BTN_4**: Ready to drive 
- **BTN_5**: Additional button

```c
typedef struct {
    enum BTN_Device id;
    struct GPIO_Tuple gpio_tuple;
    uint8_t value;
    uint8_t prev_value;
    enum BTN_State state;
    IIR_filter filter;
} BTN_handleTypedef;

void BTN_Devices_Init(BTN_handleTypedef *hbtn, float btn_IIR_alpha);
void BTN_Device_Sample(BTN_handleTypedef *hbtn);
void BTN_Device_SampleALL(BTN_handleTypedef *hbtn);
enum BTN_State BTN_Device_GetState(BTN_handleTypedef *hbtn);
```

### 4. rotary_switch
#### Inc/bsp.h Src/bsp.c
handle the 3 rotary DIP switches and define the functions for sample their position.
- **RSW1**: Power regulation
- **RSW2**: Control incidence
- **RSW3**: Additional rotary

```c
enum RSW_Device {
    RSW_Device1,
    RSW_Device2,
    RSW_Device3,
    RSW_Device_NUM
};

typedef struct {
    enum RSW_Device id;
    struct GPIO_Quad gpio_quad;
    uint8_t value[4];
    uint8_t state;
    IIR_filter filters[4];
} RSW_handleTypedef;

void RSW_Devices_Init(RSW_handleTypedef *hrsw, float rsw_IIR_alpha);
void RSW_Device_Sample(RSW_handleTypedef *hrsw);
void RSW_Device_SampleALL(RSW_handleTypedef *hrsw);
uint8_t RSW_Device_GetState(RSW_handleTypedef *hrsw);
```

### 5. can
#### Inc/can.h Src/can.c
Implements all the function needed for the CAN transmission.

```c
void CAN_build_payload(uint8_t *payload, btnStateHandleTypedef *hbtn, rswStateHandleTypedef *hrsw);
void CAN_steering_Msg_send(CAN_HandleTypeDef *hcan, uint8_t *buffer, uint8_t len);
 ```
