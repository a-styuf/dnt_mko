#include "mko_ud_header.h"

#define MKO_ADR 19

uint16 *MKO_tr_data = (uint16*)0x1000;
uint16 *MKO_rv_data = (uint16*)0x0800;

void MKO_UD_Init()
{
	BSICONFIG = 0x4005; //������������ ���������� ���������
	BSICON_TERM = ((0x1F&MKO_ADR)<<11) | 0x0001;
    INT_MASK1 |= 0x0002; //���������� ���������� �� ���
    INT_PEND1 &= ~0x0002; // ��������� ������ ����������
}

int8 MKO_data_to_transmit(uint16 *data, uint8 subaddr)
{
  uint8 i;
  if (subaddr == 0 | subaddr > 30) return -1;
  for (i=0; i<31; i++)
  {
    MKO_tr_data[i+1+(subaddr*32)] = data[i];
  }
   MKO_tr_data[0+(subaddr*32)] = data[31];
  return 0;
}

int8 MKO_receive_data(uint16 *data, uint8 subaddr)
{
  uint8 i;
  if (subaddr == 0 | subaddr > 30) return -1;
  for (i=0; i<31; i++)
  {
		data[i] =  MKO_rv_data[i+1+(subaddr*32)];
  }
  data[31] = MKO_rv_data[0+(subaddr*32)] ;
  return 0;
}

int8 MKO_receive_data_change(uint16 *data, uint8 subaddr)
{
  uint8 i;
  if (subaddr == 0 & subaddr > 30) return -1;
  for (i=0; i<31; i++)
  {
    MKO_rv_data[i+1+(subaddr*32)] = data[i];
  }
   MKO_rv_data[0+(subaddr*32)] = data[31];
  return 0;
}

uint16 MKO_State()
{
  return BSISTAT_TERM;
}
