#pragma once

#include <QString>
#include <QVector>
#include <QMetaType>

enum FriendStatus {kCallMe=60, kOnline=10, kAway=30, kBusy=50, kSilent=70, kHidden=40, kOffline=100};

enum ClientType{kPc=1, kPhone=21, kIphone=24, kWeb=41, kIpad};

Q_DECLARE_METATYPE(FriendStatus)

struct FileInfo
{
    int size_;
    QString name_;
    QString network_path_;
};

class ItemInfo
{
public:
    ItemInfo(QString id, QString name, QString mood = "") :
        id_(id),
        name_(name),
        mood_(mood)
    {}
    ItemInfo() {}
    virtual ~ItemInfo() {}

public:
    QString avatarPath() const
    {
        return avatar_path_;
    }
    void set_avatarPath(QString avatar_path)
    { avatar_path_ = avatar_path; }

    QString name() const
    { return name_; }
    void set_name(QString name)
    { name_ = name; }

    QString id() const
    { return id_; }
    void set_id(QString id)
    { id_ = id; }

    QString mood() const
    { return mood_; }
    void set_mood(QString mood)
    { mood_ = mood; }

    virtual void set_markName(QString mark_name)
    { Q_UNUSED(mark_name)}
    virtual QString markName() const
    { return name_; }

    virtual FriendStatus status() const
    { return kOnline; }
    virtual void set_status(FriendStatus status)
    { Q_UNUSED(status)}

    virtual ClientType clientType() const
    { return kPc; }
    virtual void set_clientType(ClientType type)
    { Q_UNUSED(type) }

    virtual QString gCode() const
    { return ""; }

protected:
    QString id_;
    QString name_;    
    QString mood_;
    QString avatar_path_;
};

class FriendInfo : public ItemInfo
{
public:
    FriendInfo(QString id, QString name, QString mark_name = "", QString mood = "", FriendStatus status=kOnline) :
        ItemInfo(id, name, mood),
        mark_name_(mark_name),
        status_(status)
    {}
    FriendInfo() {}

public:
    FriendStatus status() const
    { return status_; }
    void set_status(FriendStatus status)
    { status_ = status; }

    ClientType clientType() const
    { return client_type_; }
    void set_clientType(ClientType type)
    { client_type_ = type;  }

    QString markName() const
    {
        if (mark_name_.isEmpty())
            return name_;

        return mark_name_ + "-[ " + name_ + " ]";
    }

    void set_markName(QString mark_name)
    { mark_name_ = mark_name; }

private:
    QString mark_name_;
    FriendStatus status_;
    ClientType client_type_;
};

class GroupInfo : public ItemInfo
{
public:
    virtual QString gCode() const
    { return gcode_; }
    void set_gCode(QString gcode)
    { gcode_ = gcode; }

private:
    QString gcode_;
};