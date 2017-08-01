#ifndef __BASE64_H__
#define __BASE64_H__
#include <stdio.h>
#include "base64base.h"

class Base64 : public Base64Base
{
protected:
	std::string output;
	std::string outputbuffer;

public:
	//EncodeString 将输入字符串进行Base64编码，返回编码成Base64的结果字符串
	const std::string& EncodeString(const std::string& input)
	{
		output.clear();
		Encode(input, &output);
		return output;
	}
	
	//EncodeBuffer 编码一段内存数据，返回编码成Bate64的结结果字符串
	const std::string& EncodeBuffer(const char *buf, int len)
	{
		outputbuffer.clear();
		if( buf && len > 0 )
		{
			int encodelen = EncodedLength(len);
			char *encodebuf = new char[encodelen];

			if( encodebuf && Encode(buf, len, encodebuf, encodelen) )
			{
				outputbuffer += encodebuf;
			}
			if( encodebuf )
			{
				delete encodebuf;
				encodebuf = NULL;
			}
		}
		return outputbuffer;
	}
	
	//EncodeString 参数是要编码的文件路径，输出是返回编码成Base64的字符串
	const std::string& EncodeFile(const std::string& filename)
	{
		FILE *fp = 0;

		output.clear();
		if( filename.empty() )
		{
			return output;
		}
		fp = fopen(filename.data(), "r");
		while(fp)
		{
			int len = 0;
			char buf[512]={0};
			size_t encodelen = 0;
			char encodebuf[1024] = {0};

			len = fread(buf, 1, sizeof(buf), fp);
			if( len < 1 )
			{
				return output;
			}
			encodelen = EncodedLength(len);
			if( Encode(buf, len, encodebuf, encodelen) )
			{
				encodebuf[encodelen] = 0;
				output += encodebuf;
			}
		}//while
		return output;
	}//EncodeFile

	//EncodeFileToFile 参数1是要编译的文件的路径，参数2是保存编码输出的文件路径
	bool EncodeFileToFile(const std::string& filename, const std::string& outfile)
	{
		FILE *fp = 0;
		FILE *op = 0;

		output.clear();
		if( filename.empty() || outfile.empty() )
		{
			return false;
		}
		op = fopen(outfile.data(), "w");
		if( NULL == op )
		{
			return false;
		}
		fp = fopen(filename.data(), "r");
		while(fp)
		{
			int len = 0;
			char buf[512]={0};
			size_t encodelen = 0;
			char encodebuf[1024] = {0};
			int totalread = 0;
			int totalwrite = 0;

			len = fread(buf, 1, sizeof(buf), fp);
			if( len < 1 )
			{
				return totalwrite == EncodedLength(totalread);
			}
			totalread += len;
			encodelen = EncodedLength(len);
			if( Encode(buf, len, encodebuf, encodelen) )
			{
				int wlen = fwrite(encodebuf, encodelen, 1, op);
				if( wlen > 0 )
				{
					totalwrite += wlen;
				}
			}
		}//while(op)
		return false;
	}//EncodeFileToFile
};

#endif//__BASE64_H__
