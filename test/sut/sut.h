#ifndef H55F2C6C5_F6A2_4A0E_BECF_9A537AA0C416
#define H55F2C6C5_F6A2_4A0E_BECF_9A537AA0C416

#if !SUT_NO_NAMESPACE
# define SUT_NS SUT
# define SUT_NS_BEGIN namespace SUT_NS {
# define SUT_NS_END }
# define USING_SUT_NS using namespace SUT_NS;
# define SUT_FWD_DECL(type) namespace SUT_NS { struct type; }

#else
# define SUT_NS
# define SUT_NS_BEGIN
# define SUT_NS_END
# define USING_SUT_NS
# define SUT_FWD_DECL(type) struct type;
#endif


#endif
