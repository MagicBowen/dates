#ifndef H05B2224D_B926_4FC0_A936_67B52B8A98DB
#define H05B2224D_B926_4FC0_A936_67B52B8A98DB

#if !DATES_NO_NAMESPACE
# define DATES_NS DATES
# define DATES_NS_BEGIN namespace DATES_NS {
# define DATES_NS_END }
# define USING_DATES_NS using namespace DATES_NS;
# define DATES_FWD_DECL(type) namespace DATES_NS { struct type; }

#else
# define DATES_NS
# define DATES_NS_BEGIN
# define DATES_NS_END
# define USING_DATES_NS
# define DATES_FWD_DECL(type) struct type;
#endif

#endif
