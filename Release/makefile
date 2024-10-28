################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/MUSART/subdir.mk
-include MCAL/MTWI/subdir.mk
-include MCAL/MSPI/subdir.mk
-include MCAL/MGIE/subdir.mk
-include MCAL/MDIO/subdir.mk
-include MCAL/MADC/subdir.mk
-include HAL/HLED/subdir.mk
-include HAL/HEEPROM/subdir.mk
-include HAL/HCLCD/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ADC_LCD_Semphore.lss \

FLASH_IMAGE += \
ADC_LCD_Semphore.hex \

EEPROM_IMAGE += \
ADC_LCD_Semphore.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ADC_LCD_Semphore.elf secondary-outputs

# Tool invocations
ADC_LCD_Semphore.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ADC_LCD_Semphore.map -mmcu=atmega32 -o "ADC_LCD_Semphore.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ADC_LCD_Semphore.lss: ADC_LCD_Semphore.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ADC_LCD_Semphore.elf  >"ADC_LCD_Semphore.lss"
	@echo 'Finished building: $@'
	@echo ' '

ADC_LCD_Semphore.hex: ADC_LCD_Semphore.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ADC_LCD_Semphore.elf  "ADC_LCD_Semphore.hex"
	@echo 'Finished building: $@'
	@echo ' '

ADC_LCD_Semphore.eep: ADC_LCD_Semphore.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ADC_LCD_Semphore.elf  "ADC_LCD_Semphore.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ADC_LCD_Semphore.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ADC_LCD_Semphore.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ADC_LCD_Semphore.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
