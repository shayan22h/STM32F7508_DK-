<h1>Sensor With ADC Interface</h1> 
<p> The Idea behind this project  is,  a sensor with ADC interface is connected to STM32f7508 Discovery Board the adc value is read and transmitted on a serial line </P>
<p> Furthermore I have added cofngiurations for Timer Delay of micro seconds, Extinterrupt GPIO as input and GPIO ouptut in this project even though they are not relevent to the project concept   </P>

<h2>ADC-SubComponent</h2>

This project has configured ADC 3 Channel 0 with 8 bit Resolution to Read an analouge value on Pin PA0.
ADC start in the thread an Interrupt mode where by the end of conversion, an interrupt callback is used to transmit the value on a serial (UART1) line

<h2>UART-SubComponent</h2>

<h2>EXTI_GPIO as subcomponent</h2>

<h2></h2>