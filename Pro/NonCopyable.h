#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class NonCopyable 			//禁用值语意
{
    public:
        NonCopyable() { }
        ~NonCopyable() { }
    private:
        NonCopyable(const NonCopyable &);
        void operator= (const NonCopyable &);
};

#endif  /*NON_COPYABLE_H*/
