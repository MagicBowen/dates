#ifndef H6AD31F32_8D67_41B0_BB69_D2F7517D2DF8
#define H6AD31F32_8D67_41B0_BB69_D2F7517D2DF8

#include <dates/extend/fake/FakeSystem.h>
#include <dates/extend/fake/FakeName.h>
#include <msgcc/Msgcc.h>
#include <functional>

DATES_NS_BEGIN

#define __def_fake_system_begin(NAME)               \
struct FAKE(NAME) : private FakeSystem              \
{                                                   \
    FAKE(NAME)(Runtime& runtime)                    \
    : FakeSystem(#NAME, runtime)                    \
    {}

#define __def_fake_system_end                       };

///////////////////////////////////////////////////////
#define __could_send(MSG)                                   \
void send(const std::function<void (FAKE(MSG)&)>& builder)  \
{                                                           \
    FakeSystemBase::send(builder);                          \
}

#define __could_recv(MSG)                                   \
void recv(const std::function<void (const FAKE(MSG)&)>& checker)\
{                                                           \
    FakeSystemBase::recv(checker);                          \
}

///////////////////////////////////////////////////////
#define __msgcc_send(MSG)                                   \
void send(const std::function<void (FAKE(MSG)&)>& builder)  \
{                                                           \
    FakeSystemBase::send([&](FAKE(MSG)& msg)                \
                        {                                   \
                            Msgcc<MSG>::construct(msg);     \
                            builder(msg);                   \
                        });                                 \
}

#define __msgcc_recv(MSG)                                   \
void recv(const std::function<void (const FAKE(MSG)&)>& checker)\
{                                                           \
    FakeSystemBase::recv([&](const FAKE(MSG)& msg)          \
                        {                                   \
                            Msgcc<MSG>::check(msg);         \
                            checker(msg);                   \
                        });                                 \
}

DATES_NS_END

#endif
