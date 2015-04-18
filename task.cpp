#include "task.h"

#include <QTimer>
#include <QEventLoop>

namespace tasks
{

task_token::task_token()
    : canceled_(false)
{
}

void task_token::cancel()
{
    canceled_ = true;
//    emit canceled();
}

////////////////////////////////////////////////////////////////////////////////

task_base::task_base()
    : finished_(false)
    , has_error_(false)
{

}

task_base::~task_base()
{

}

//task_token_p task_base::token()
//{
//}

void task_base::cancel()
{

}

task_p task_base::continue_with(const task_p& t)
{
    continue_with_.push_back(t);
    return t;
}

task_p task_base::continue_with(const std::function<void(task_p)>& action)
{
    auto self = shared_from_this();
    return continue_with(std::make_shared<action_task>([self, action]()
    {
        action(self);
    }));
}

//{
//    task_p res = std::make_shared<TaskSimple>();
//    auto f = [func, res](task_p prev)
//    {
////        if (res->isCanceled())
////        func();
////        res



//    };
////    continue_with_.append(f);
//}


void task_base::wait()
{
//    if (finished_)
//        return;
//    QEventLoop loop;
//    connect(this, &task_base::finished, &loop, &QEventLoop::quit);
//    loop.exec();
}

void task_base::wait_and_check()
{
    wait();
    if (has_error())
        throw std::runtime_error("error");
}

void task_base::start()
{

}

void task_base::process_finish()
{
    finished_ = true;
//    emit finished();
    for (auto func : continue_with_)
    {
        func->start();
    }
}

void task_base::set_error()
{
    has_error_ = true;
}


Delay::Delay()
    : timer_(new QTimer(this))
{
    timer_->setSingleShot(true);
    connect(timer_, &QTimer::timeout, this, &Delay::finish);
}

task_p Delay::start(int msecs)
{
    auto res = std::make_shared<Delay>();
    res->timer_->start(msecs);
    return res;
}

void Delay::finish()
{
    process_finish();
}

action_task::action_task(const std::function<void()>& action)
    : action_(action)
{
}

void action_task::start()
{
    try
    {
        action_();
    }
    catch(...)
    {
        set_error();
    }
    process_finish();
}

}
