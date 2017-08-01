#include <stdio.h>
#include "base64.h"
using namespace std;

int main(void)
{
	Base64 encoder;

	//EncodeString 将输入字符串进行Base64编码，返回编码成Base64的结果字符串
	printf("%s\n", encoder.EncodeString("this is the base64").data());
	
	//EncodeBuffer 编码一段内存数据，返回编码成Bate64的结结果字符串
	printf("%s\n", encoder.EncodeBuffer("ttbufer", 7).data());
	
	//EncodeString 参数是要编码的文件路径，输出是返回编码成Base64的字符串
	printf("%s\n", encoder.EncodeFile("tt.tar").data());
	
	//EncodeFileToFile 参数1是要编译的文件的路径，参数2是保存编码输出的文件路径
	encoder.EncodeFileToFile("tt.tar", "output2");

	return 0;
}