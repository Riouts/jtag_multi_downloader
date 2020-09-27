float DS18B20_Get_Temp(uint8_t *a,uint16_t go_temp,uint8_t b)
{
  uint8_t tpmsb, tplsb;
  short s_tem;
  float f_tem;
  int temp_num;
  DS18B20_Rst();   
  DS18B20_Presence();  
  DS18B20_Write_Byte(0XCC); // ?? ROM 
  DS18B20_Match_Serial(b); //?????
  DS18B20_Write_Byte(0X44); // ???? 
  DS18B20_Rst();
  DS18B20_Presence();
  DS18B20_Write_Byte(0XCC); //?? ROM  
  DS18B20_Match_Serial(b); //?????
  DS18B20_Write_Byte(0XBE); //???? 
  tplsb = DS18B20_Read_Byte();  
  tpmsb = DS18B20_Read_Byte(); 
  s_tem = tpmsb<<8;
  s_tem = s_tem | tplsb;
  if( s_tem < 0 ) //???
  {
    f_tem = (~s_tem+1) * 0.0625;    
	temp_num = (~s_tem+1) * 0.0625*10;    
	go_temp= temp_num;    
	if(temp_num>=1000)    
		{       a[0]='-';       a[1]= temp_num/1000+'0';       a[2]= temp_num%1000/100+'0';       a[3]= temp_num%100/10+'0';       a[4]='.';       a[5]= temp_num%10+'0';       a[6]= '\0';    }    else    {       a[0]='-';       a[1]= temp_num/100+'0';       a[2]= temp_num%100/10+'0';       a[3]='.';        a[4]=temp_num%10+'0';       a[5]= '\0';    }
  } 
  else
  {
    f_tem = s_tem * 0.0625;    temp_num = s_tem * 0.0625*10;    go_temp= temp_num;    if(temp_num>=1000)    {       a[0]='+';       a[1]= temp_num/1000+'0';       a[2]= temp_num%1000/100+'0';       a[3]= temp_num%100/10+'0';       a[4]='.';       a[5]= temp_num%10+'0';       a[6]= '\0';
    }   else   {       a[0]='+';       a[1]= temp_num/100+'0';       a[2]= temp_num%100/10+'0';       a[3]='.';        a[4]=temp_num%10+'0';       a[5]= '\0';    }
  } 
  return f_tem; 
}

---------------------

???? xxcccm ?CSDN ?? ,???????:https://blog.csdn.net/xuxuechen/article/details/40830003?utm_source=copy 