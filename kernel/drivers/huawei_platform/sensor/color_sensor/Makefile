#
# Makefile for ams TCS3430 device.
#
ifdef CONFIG_SENSORS_COLOR_AP

#
# Feature Options
#

ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_AMS_OPTICAL_SENSOR_ALS
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_AMS_OPTICAL_SENSOR_ALS_XYZ
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_AMS_DEBUG_LOG
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_ROHM_DEBUG_LOG
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_ROHM_OPTICAL_SENSOR_ALS
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -DCONFIG_ROHM_OPTICAL_SENSOR_ALS_XYZ
#
# Include Paths
#
ccflags-$(CONFIG_SENSORS_COLOR_AP)	+= -I$(src)

#
# Object Artifacts
obj-$(CONFIG_SENSORS_COLOR_AP)	+= color_sensor.o rohm_bh1749.o ams_tcs3430.o ams_tcs3707.o rohm_bu27006.o

endif
