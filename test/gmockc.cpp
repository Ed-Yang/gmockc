#include <memory.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

/* include the prototype of mock function */
#include "xdev.h"

using namespace ::testing;

/* according GMock requirement to declare the mock function   */
class XDevMock
{
public:
    virtual ~XDevMock(){}
    /**
     * MOCK_METHOD1: the function take one parameter
     * int (int): the return type is 'int' and the parameter is also 'int' type
     * 
     */
    MOCK_METHOD1(xdev_get_link_status, int (int));
};

/* GTest test fixture. Use for test case setup and tear down  */
class TestFixture : public ::testing::Test
{
public:
    TestFixture()
    {
        /* allocatet the mock object */
        _devMock.reset(new ::testing::NiceMock<XDevMock>());
    }

    ~TestFixture()
    {
        /* free the mock object */
        _devMock.reset();
    }
    virtual void SetUp(){}
    virtual void TearDown(){}

    static std::unique_ptr<XDevMock> _devMock;
};

/* make the class static member accessible to other function */
std::unique_ptr<XDevMock>  TestFixture::_devMock;

/* mock function */
int xdev_get_link_status(int port)
{
    int retval;

    /* invoke GMock function */
    retval = TestFixture::_devMock->xdev_get_link_status(port);

    return retval;
}

/* test class */
class XDevUnitTest : public TestFixture
{
public:
    XDevUnitTest() {}
};

TEST_F(XDevUnitTest, Port1)
{
    /* 
     * expect call xdev_get_link_status for port 1 twice, first time return 0, 
     * and next time return 1 
     */
    EXPECT_CALL(*_devMock,
                xdev_get_link_status(1)).Times(2).WillOnce(Return(0)).WillOnce(Return(1));

    /* test if 1st call is return 0 */
    EXPECT_EQ(0, xdev_get_link_status(1));

    /* test if 2nd call is return 0 */
    EXPECT_EQ(1, xdev_get_link_status(1));
}

TEST_F(XDevUnitTest, Port2)
{
    /* 
     * expect call xdev_get_link_status for port 2, always return 1
     */
    EXPECT_CALL(*_devMock,
                xdev_get_link_status(2)).WillRepeatedly(Return(1));

    /* test two times */
    EXPECT_EQ(1, xdev_get_link_status(2));
    EXPECT_EQ(1, xdev_get_link_status(2));
}

/* 
 * If it doesn't need to do any initialization, it is not necessary to 
 * implement main 
 */
#if 0
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif





