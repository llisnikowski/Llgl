#include <gtest/gtest.h>
#include <llgl/Attributes.hpp>
#include <string>

class Attrib1
{
public:
	Attrib1(int i1=0, int i2=0, int i3=0)
	:i{i1, i2, i3}
	{}
	static constexpr std::size_t argsNumber(){return 3;}
    static constexpr GLenum argsType(){return llgl::getGlType<int>();}
	static std::string getName() {return "Attrib1";}
	int i[3];
};

class Attrib2
{
public:
	Attrib2(float i1=0.f, float i2=0.f)
	:i{i1, i2}
	{}
	static constexpr std::size_t argsNumber(){return 2;}
    static constexpr GLenum argsType(){return llgl::getGlType<float>();}
	static std::string getName(){return "Attrib2";}
	float i[2];
};

class Attributes_test : public ::testing::Test
{
public:
	Attributes_test()
	:attributes{{
		{{1, 2, 3}, {0.1, 0.6}},
		{{2, 5, 7}, {-0.5, 12.0}}
	}}
	{}

	llgl::Attributes<Attrib1, Attrib2> attributes;
};

TEST_F(Attributes_test, attributesSize)
{
	EXPECT_EQ(attributes.attributesSize(), sizeof(std::tuple<Attrib1, Attrib2>));
}

TEST_F(Attributes_test, attributesListLength)
{
	EXPECT_EQ(attributes.attributesListLength(), 2);
}

TEST_F(Attributes_test, fullSize)
{
	EXPECT_EQ(attributes.fullSize(), 2 * sizeof(std::tuple<Attrib1, Attrib2>));
}