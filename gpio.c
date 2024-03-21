
#include "type.h"
#include "ch554.h"
#include "system.h"
#include "gpio.h"

/*******************************************************************************
* Function Name  : CH554GPIODrivCap(UINT8 Port,UINT8 Cap)
* Description    : �˿�0��1��2��3������������
* Input          : UINT8 Port�˿�ѡ��(0��1��2��3)
                   UINT8 Cap��������ѡ��((0)5mA��(1)20mA(ע��:P1����10mA))
* Output         : None
* Return         : SUCCESS�ɹ�
                   FAILʧ��
*******************************************************************************/
UINT8 CH554GPIODrivCap(UINT8 Port,UINT8 Cap)
{
    if (Port >= 4)
    {
    	return FAIL;
    }
    
    if (Cap == 0)
    {                                                               //�����������5mA
        PORT_CFG &= ~(bP0_DRV << Port);
    }
    else
    {		
        PORT_CFG |= (bP0_DRV << Port);                                             //�����������20mA
    }

    return SUCCESS;
}

/*******************************************************************************
* Function Name  : CH554GPIOModeSelt(UINT8 Port,UINT8 Mode,UINT8 PinNum)
* Description    : �˿�0��1��2��3����ģʽ����
* Input          : UINT8 Port�˿�ѡ��(0��1��2��3)
                   UINT8 Cap������ʽѡ��(bPn_OC & Pn_DIR & Pn_PU)
                   0(000)�������룬��������
                   1(001)�������룬��������
                   2(01x)������������ߵ͵�ƽǿ������
                   3(100)����©�������������֧�����룻
                   4(110)����©�����������,��ת������ɵ͵���ʱ��������2��ʱ�ӵĸߵ�ƽ
                   5(101)��׼˫��(��׼51ģʽ)����©�����������
                   6(111)��׼˫��(��׼51ģʽ)����©���������������ת������ɵ͵���ʱ��������2��ʱ�ӵĸߵ�ƽ
                   UINT8 PinNum(����ѡ��0-7)
* Output         : None
* Return         : SUCCESS�ɹ�
                   FAILʧ��
*******************************************************************************/
UINT8 CH554GPIOModeSelt(UINT8 Port,UINT8 Mode,UINT8 PinNum)
{
    UINT8 Pn_DIR,Pn_PU;
    if (Port >= 4) {
    	return FAIL;
    }

    switch (Port) {
    case 0:
        return FAIL;

    case 1:
        Pn_DIR = P1_DIR;
		Pn_PU = P1_PU;
        break;

    case 2:
        return FAIL;

    case 3:
        Pn_DIR = P3_DIR;
		Pn_PU = P3_PU;
        break;
    }
    
    switch (Mode) {
    case 0:                              //�����룬������
    	PORT_CFG &= ~(bP0_OC << Port);
    	Pn_DIR &= ~(1<<PinNum);
    	Pn_PU &= ~(1<<PinNum);
    	break;
    	
    case 1:                              //�����룬������
    	PORT_CFG &= ~(bP0_OC << Port);
    	Pn_DIR &= ~(1<<PinNum);
    	Pn_PU |= 1<<PinNum;
    	break;
    	
    case 2:                              //����������ߵ͵�ƽǿ����
    	PORT_CFG &= ~(bP0_OC << Port);
    	Pn_DIR |= (1<<PinNum);
    	break;
    	
    case 3:                              //��©�������������֧������
    	PORT_CFG |= (bP0_OC << Port);
    	Pn_DIR &= ~(1<<PinNum);
    	Pn_PU &= ~(1<<PinNum);
    	break;
    	
    default:
    	break;
    }

    switch (Port) {
    case 0:
        P0_DIR = Pn_DIR;
		P0_PU = Pn_PU;
        break;

    case 1:
        P1_DIR = Pn_DIR;
		P1_PU = Pn_PU;
        break;

    case 2:
        P2_DIR = Pn_DIR;
		P2_PU = Pn_PU;
        break;

    case 3:
        P3_DIR = Pn_DIR;
		P3_PU = Pn_PU;
        break;
    }

    return SUCCESS;
}


