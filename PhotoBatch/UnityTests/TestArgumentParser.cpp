//#include <gtest/gtest.h>
//#include <array>
//#include "../ArgumentParser.h"
//
//TEST(TestArgumentParser, RegisterFlag)
//{
//	ArgumentParser argParse;
//
//	EXPECT_FALSE(argParse.IsFlagRegistered("MyFlag"));
//
//	//registrando a flag
//	argParse.RegisterFlag("MyFlag");
//
//	//testando após o registro
//	EXPECT_TRUE(argParse.IsFlagRegistered("MyFlag"));
//}
//
//TEST(TestArgumentParser, RegisterFlag_WhiteSpace)
//{
//	ArgumentParser argParse;
//
//	//registrando a flag
//	argParse.RegisterFlag("MyFlag");
//
//	//testando após o registro
//	EXPECT_TRUE(argParse.IsFlagRegistered("MyFlag"));
//
//}
//
//TEST(TestArgumentParser, RegisterOption)
//{
//	ArgumentParser argParse;
//
//	//registrando o Option
//	argParse.RegisterOption("MyOption");
//
//	//testando após o registro
//	EXPECT_TRUE(argParse.IsOptionRegistered("MyOption"));
//
//}
//
//TEST(TestArgumentParser, RegisterOption_WhiteSpace)
//{
//	ArgumentParser argParse;
//
//	//registrando o Option
//	argParse.RegisterOption("My Option");
//
//	//testando após o registro
//	EXPECT_FALSE(argParse.IsOptionRegistered("My Option"));
//
//}
//
//TEST(TestArgumentParser, Parse)
//{
//	ArgumentParser argParse;
//
//	std::array<const char*, 5> args = {
//		"TestArgumentParser",
//		"--flag",
//		"--string=AaBbCcDd",
//		"--number=42",
//		"--float=4.2"
//	};
//
//	argParse.RegisterFlag("flag");
//	argParse.RegisterOption("string");
//	argParse.RegisterOption("number");
//	argParse.RegisterOption("float");
//	
//	argParse.Parse(static_cast<int>(args.size()), args.data());
//
//	EXPECT_FALSE(argParse.GetFlag("unregisteredFlag"));
//	EXPECT_TRUE(argParse.GetFlag("flag"));
//	EXPECT_EQ(argParse.GetOptionAs<const string&>("string"), "aabbccdd");
//	EXPECT_EQ(argParse.GetOptionAs<int>("number"), 42);
//	EXPECT_EQ(argParse.GetOptionAs<float>("float"), 4.2f);
//}
//
//TEST(TestArgumentParser, Parse_InvalidArguments)
//{
//	ArgumentParser argParse;
//
//	argParse.Parse(0, nullptr);
//	argParse.Parse(40, nullptr);
//	
//}