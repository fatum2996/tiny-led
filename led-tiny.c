#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 9600000UL

volatile unsigned char dcl;
volatile unsigned char counter;
ISR(TIM0_OVF_vect) {

}

int main(void)
{
	cli();
	dcl = 1;
	counter = 0;
	char i = 0;	
	char turndelay=255;
	DDRB = 0b000011;
	OCR0A = 0;
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000010; //1/8
	PORTB = 0;
	for(i=0; i<255; i++) {
		_delay_ms(8);
		OCR0A++;
	}
	OCR0A=255;

    while(1)
    {
		i = PINB;
		if(i & (1<<PB3)) { //���� ����� �������� ����������
			OCR0A=0;
			PORTB |= 1 << PB1;
			turndelay = 0;
		}
		else { //���� ������� �� ��������� ������������ ���
			PORTB &= ~(1<< PB1); //��������� �����������
			if(i & (1<<PB2)) {  //���� ������ ������ �� ����������
				if(turndelay == 255)
				{
					if(OCR0A > 51) { //���� ����� ����������
						while(OCR0A > 51) {				
							OCR0A--;
							_delay_ms(8);
						}
					}
					if(OCR0A < 51) { //��� ���� ���� �����������
						while(OCR0A < 51) {				
							OCR0A++;
							_delay_ms(8);
						}
					}
				}
				else {
					turndelay++;
					_delay_ms(4);
				}
			}
			else { //���������� ��� ���������� ������������
				if(turndelay == 255) { // ���� ��������� ��� � ������
					if(OCR0A!=255) { //���� ��� �� �����������
						while(OCR0A != 255) {				
							OCR0A++;
							_delay_ms(8);
						}
					}
				}
				else {
					turndelay++;
					_delay_ms(4);
				}
			}
		}
	}
}
