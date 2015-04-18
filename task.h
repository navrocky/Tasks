#pragma once

#include <QObject>
#include <QTimer>

#include <functional>
#include <memory>
#include <type_traits>

namespace tasks
{

class task_base;
typedef std::shared_ptr<task_base> task_p;

template <class Result, class Enabled = void>
class task;

class task_token;
typedef std::shared_ptr<task_token> task_token_p;

template <class T>
using action = std::function<void(const T&)>;

template <typename T>
using enable_if_void = typename std::enable_if<std::is_void<T>::value>::type;


//typedef std::function<void()> action;
//typedef std::function<void(task_p)> action_with_task;

class task_token : public std::enable_shared_from_this<task_token>
{
public:
    task_token();

    void is_canceled() const;

//signals:
//    void canceled();

private:
    void cancel();
    bool canceled_;
};

class task_base : public std::enable_shared_from_this<task_base>
{
public:
    task_base();
    virtual ~task_base();

//    task_token_p token();

    virtual void cancel();

//    qreal progress() const;

//    task_p continue_with(std::function<void()> func);
    task_p continue_with(const task_p& t);
    task_p continue_with(const std::function<void(task_p)>& action);

    template <typename Result>
    std::shared_ptr<task<Result>> continue_with(const std::function<Result(task_p)>& func)
    {



    }

    void wait();
    void wait_and_check();

    bool has_error() const { return has_error_; }

//signals:
//    void finished();
//    void progressChanged();

protected:
    virtual void start();
    virtual void process_finish();

    void set_error();

private:
    task_base(const task_base&);
    task_base& operator=(const task_base&);

    bool finished_;
    bool has_error_;
    std::list<task_p> continue_with_;
};

template <class Result, class Enable>
class task : public task_base
{
public:
    task() : result_() {}

    Result result() const { return result_; }

private:
    Result result_;
};


template <class Result>
class task<Result, enable_if_void<Result> > : public task_base
{
public:
};



class action_task : public task_base
{
public:
    action_task(const std::function<void()>& action);

//    using task_base::process_finish;
protected:
    void start() override;

private:
    std::function<void()> action_;
};




class Delay : public QObject, public task_base
{
    Q_OBJECT
public:
    Delay();
    static task_p start(int msecs);

private:
    void finish();

    QTimer* timer_;
};

}
