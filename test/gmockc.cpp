#include <memory> /* for gcc 4.9.2, also have to define -std=c++11 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

/* include the prototype of mock function */
#include "xdev.h"

using namespace ::testing;

/**
 * XDevMock
 * GMock macro to define the mock API 
 *
 * MOCK_METHOD1: the function take one parameter
 * int (int): the return type is 'int' and the parameter is also 'int' type
 * 
 */
class XDevMock
{
public:
    virtual ~XDevMock(){}

    /* mock api */
    MOCK_METHOD1(xdev_get_link_status, int (int));
};

/**
 * XDevUnitTest
 * 
 * GTest test fixture and unit test class . Used for instanlize test class and
 * test case setup and tear down  
 * 
 * @param _devMock pointer to test class, enable external access to test object
 */
class XDevUnitTest : public ::testing::Test
{
public:
    XDevUnitTest()
    {
        /* allocatet the mock object */
        _devMock.reset(new ::testing::NiceMock<XDevMock>());
    }

    ~XDevUnitTest()
    {
        /* free the mock object */
        _devMock.reset();
    }
    virtual void SetUp(){}
    virtual void TearDown(){}

    static std::unique_ptr<XDevMock> _devMock;
};

/* make the class static member accessible to other function */
std::unique_ptr<XDevMock>  XDevUnitTest::_devMock;

/* mock function */
int xdev_get_link_status(int port)
{
    int retval;

    /* invoke GMock function through classs static member */
    retval = XDevUnitTest::_devMock->xdev_get_link_status(port);

    return retval;
}

/* test case 1 */
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

    /* test if 2nd call is return 1 */
    EXPECT_EQ(1, xdev_get_link_status(1));
}

/* test case 1 */
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





