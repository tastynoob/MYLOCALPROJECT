import sensor, image, lcd, time,math
import KPU as kpu
import gc, sys,time
from machine import I2C



SMPLRT_DIV	=	0x19
CONFIG		=	0x1A
GYRO_CONFIG		=0x1B
ACCEL_CONFIG	=0x1C
ACCEL_XOUT_H=	0x3B
ACCEL_XOUT_L=	0x3C
ACCEL_YOUT_H=	0x3D
ACCEL_YOUT_L=	0x3E
ACCEL_ZOUT_H=	0x3F
ACCEL_ZOUT_L=	0x40
TEMP_OUT_H	=	0x41
TEMP_OUT_L	=	0x42
GYRO_XOUT_H	=	0x43
GYRO_XOUT_L	=	0x44
GYRO_YOUT_H	=	0x45
GYRO_YOUT_L	=	0x46
GYRO_ZOUT_H	=	0x47
GYRO_ZOUT_L	=	0x48
PWR_MGMT_1	=	0x6B
WHO_AM_I	=		0x75
SlaveAddress=	0xD0
MPU_60X0_PWR_MGMT_1_REG_ADDR=        0x6B
MPU_60X0_USER_CTRL_REG_ADDR  =       0x6A
MPU_60X0_SMPLRT_DIV_REG_ADDR  =      0x19
MPU_60X0_CONFIG_REG_ADDR       =     0x1A
MPU_60X0_GYRO_CONFIG_REG_ADDR   =    0x1B
MPU_60X0_ACCEL_CONFIG_REG_ADDR    =  0x1C
MPU_60X0_FIFO_EN_REG_ADDR        =   0x23
MPU_60X0_RESET_REG_VALU      =       0x80
MPU_60X0_PWR_MGMT_1_REG_VALU  =      0x09
MPU_60X0_USER_CTRL_REG_VALU    =     0x45
MPU_60X0_SMPLRT_DIV_REG_VALU    =    0x00
MPU_60X0_CONFIG_REG_VALU         =   0x03
MPU_60X0_GYRO_CONFIG_REG_VALU =      0x18
MPU_60X0_ACCEL_CONFIG_REG_VALU =     0x00
MPU_60X0_FIFO_EN_REG_VALU       =    0x78



class MPU6050:
	devices=[]
	def init(self,i2c):
		self.devices = i2c.scan()
		print(self.devices)
		i2c.writeto_mem(self.devices[0],MPU_60X0_PWR_MGMT_1_REG_ADDR, MPU_60X0_RESET_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_PWR_MGMT_1_REG_ADDR, MPU_60X0_PWR_MGMT_1_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_USER_CTRL_REG_ADDR, MPU_60X0_USER_CTRL_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_SMPLRT_DIV_REG_ADDR, MPU_60X0_SMPLRT_DIV_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_CONFIG_REG_ADDR, MPU_60X0_CONFIG_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_GYRO_CONFIG_REG_ADDR, MPU_60X0_GYRO_CONFIG_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_ACCEL_CONFIG_REG_ADDR, MPU_60X0_ACCEL_CONFIG_REG_VALU)
		time.sleep_ms(10)
		i2c.writeto_mem(self.devices[0],MPU_60X0_FIFO_EN_REG_ADDR, MPU_60X0_FIFO_EN_REG_VALU)

	def getAcx(self):
		a=i2c.readfrom_mem(self.devices[0],ACCEL_XOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return (- (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1))/16.4
	def getAcy(self):
		a=i2c.readfrom_mem(self.devices[0],ACCEL_YOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return (- (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1))/16.4
	def getAcz(self):
		a=i2c.readfrom_mem(self.devices[0],ACCEL_ZOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return (- (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1))/16.4


	def getGyx(self):
		a=i2c.readfrom_mem(self.devices[0],GYRO_XOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return - (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1)
	def getGyy(self):
		a=i2c.readfrom_mem(self.devices[0],GYRO_YOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return - (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1)
	def getGyz(self):
		a=i2c.readfrom_mem(self.devices[0],GYRO_ZOUT_H,2)
		if not a[0] & 0x80:
			return a[0] << 8 | a[1]
		return - (((a[0] ^ 255) << 8) | (a[1] ^ 255) + 1)
	def anglex(self):
		a=self.getAcz()
		b=self.getAcx()
		if b==0:
			b=0.0001
		return math.atan(a/b)*(180/math.pi)
	def angley(self):
		a=self.getAcy()
		b=self.getAcx()
		if b==0:
			b=0.0001
		return math.atan(a/b)*(180/math.pi)
	def anglez(self):
		a=self.getAcx()
		b=self.getAcz()
		if b==0:
			b=0.0001
		return math.atan(a/b)*(180/math.pi)


mpu6050 = MPU6050()




