/****************************************************************************
** Meta object code from reading C++ file 'app_protocol_set_config.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Config_Tool/app/app_protocol_set_config.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'app_protocol_set_config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN20AppProtocolSetConfigE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN20AppProtocolSetConfigE = QtMocHelpers::stringData(
    "AppProtocolSetConfig",
    "recv_scene_data_result",
    "",
    "success",
    "sceneListChanged",
    "QList<scene_save_t>",
    "data",
    "bindListChanged",
    "QList<bind_save_t>",
    "sigUpdate",
    "const timer_task_t*",
    "tasks",
    "recv_serial_data",
    "recv_scene_data",
    "QList<panel_data_t>",
    "panels",
    "QList<led_data_t>",
    "leds",
    "QList<relay_data_t>",
    "relays",
    "uint8_t",
    "scene_id",
    "name",
    "recv_bind_data",
    "panelAddr",
    "keyIndex",
    "sceneId",
    "isOpen",
    "bulidSceneData",
    "buildBindData",
    "addr",
    "key_num",
    "state",
    "scene_name",
    "deleteScene",
    "deleteBind",
    "bind_save_t",
    "bind",
    "getAllConfigData",
    "config_data_t",
    "getAllBindData",
    "bind_data_t",
    "getSceneConfigDataById",
    "setAllConfigData",
    "setAllBindData",
    "binds",
    "sendSceneData",
    "sendBindData",
    "sendClearSceneData",
    "sendClearBindData",
    "sendGetTimerTask",
    "sendSetTimerTask",
    "sendCalTime",
    "uint64_t",
    "time",
    "configIsChanged",
    "clearConfigChanged",
    "packFrame",
    "payload",
    "cmdType"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN20AppProtocolSetConfigE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  170,    2, 0x06,    1 /* Public */,
       4,    1,  173,    2, 0x06,    3 /* Public */,
       7,    1,  176,    2, 0x06,    5 /* Public */,
       9,    1,  179,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    1,  182,    2, 0x0a,    9 /* Public */,
      13,    5,  185,    2, 0x0a,   11 /* Public */,
      23,    4,  196,    2, 0x0a,   17 /* Public */,
      28,    5,  205,    2, 0x0a,   22 /* Public */,
      29,    5,  216,    2, 0x0a,   28 /* Public */,
      34,    1,  227,    2, 0x0a,   34 /* Public */,
      35,    1,  230,    2, 0x0a,   36 /* Public */,
      38,    0,  233,    2, 0x10a,   38 /* Public | MethodIsConst  */,
      40,    0,  234,    2, 0x10a,   39 /* Public | MethodIsConst  */,
      42,    1,  235,    2, 0x10a,   40 /* Public | MethodIsConst  */,
      43,    1,  238,    2, 0x0a,   42 /* Public */,
      44,    1,  241,    2, 0x0a,   44 /* Public */,
      46,    0,  244,    2, 0x0a,   46 /* Public */,
      47,    0,  245,    2, 0x0a,   47 /* Public */,
      48,    0,  246,    2, 0x0a,   48 /* Public */,
      49,    0,  247,    2, 0x0a,   49 /* Public */,
      50,    0,  248,    2, 0x0a,   50 /* Public */,
      51,    1,  249,    2, 0x0a,   51 /* Public */,
      52,    1,  252,    2, 0x0a,   53 /* Public */,
      55,    0,  255,    2, 0x0a,   55 /* Public */,
      56,    0,  256,    2, 0x0a,   56 /* Public */,
      57,    2,  257,    2, 0x0a,   57 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    6,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16, 0x80000000 | 18, 0x80000000 | 20, QMetaType::QString,   15,   17,   19,   21,   22,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Int, 0x80000000 | 20, QMetaType::Bool,   24,   25,   26,   27,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16, 0x80000000 | 18, 0x80000000 | 20, QMetaType::QString,   15,   17,   19,   21,   22,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 20, 0x80000000 | 20, 0x80000000 | 20, QMetaType::QString,   30,   31,   32,   21,   33,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 36,   37,
    0x80000000 | 39,
    0x80000000 | 41,
    0x80000000 | 39, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 39,    6,
    QMetaType::Void, 0x80000000 | 41,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, 0x80000000 | 53,   54,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::QByteArray, QMetaType::QByteArray, 0x80000000 | 20,   58,   59,

       0        // eod
};

Q_CONSTINIT const QMetaObject AppProtocolSetConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN20AppProtocolSetConfigE.offsetsAndSizes,
    qt_meta_data_ZN20AppProtocolSetConfigE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN20AppProtocolSetConfigE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AppProtocolSetConfig, std::true_type>,
        // method 'recv_scene_data_result'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'sceneListChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<scene_save_t> &, std::false_type>,
        // method 'bindListChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<bind_save_t> &, std::false_type>,
        // method 'sigUpdate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const timer_task_t *, std::false_type>,
        // method 'recv_serial_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'recv_scene_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<panel_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<led_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<relay_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'recv_bind_data'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'bulidSceneData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<panel_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<led_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<relay_data_t> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'buildBindData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'deleteScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        // method 'deleteBind'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bind_save_t &, std::false_type>,
        // method 'getAllConfigData'
        QtPrivate::TypeAndForceComplete<config_data_t, std::false_type>,
        // method 'getAllBindData'
        QtPrivate::TypeAndForceComplete<bind_data_t, std::false_type>,
        // method 'getSceneConfigDataById'
        QtPrivate::TypeAndForceComplete<config_data_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>,
        // method 'setAllConfigData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const config_data_t &, std::false_type>,
        // method 'setAllBindData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bind_data_t &, std::false_type>,
        // method 'sendSceneData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendBindData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendClearSceneData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendClearBindData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendGetTimerTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendSetTimerTask'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        // method 'sendCalTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const uint64_t &, std::false_type>,
        // method 'configIsChanged'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'clearConfigChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'packFrame'
        QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const uint8_t, std::false_type>
    >,
    nullptr
} };

void AppProtocolSetConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AppProtocolSetConfig *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->recv_scene_data_result((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->sceneListChanged((*reinterpret_cast< std::add_pointer_t<QList<scene_save_t>>>(_a[1]))); break;
        case 2: _t->bindListChanged((*reinterpret_cast< std::add_pointer_t<QList<bind_save_t>>>(_a[1]))); break;
        case 3: _t->sigUpdate((*reinterpret_cast< std::add_pointer_t<const timer_task_t*>>(_a[1]))); break;
        case 4: _t->recv_serial_data((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 5: _t->recv_scene_data((*reinterpret_cast< std::add_pointer_t<QList<panel_data_t>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<led_data_t>>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QList<relay_data_t>>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 6: _t->recv_bind_data((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4]))); break;
        case 7: _t->bulidSceneData((*reinterpret_cast< std::add_pointer_t<QList<panel_data_t>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<led_data_t>>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QList<relay_data_t>>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 8: _t->buildBindData((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5]))); break;
        case 9: _t->deleteScene((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1]))); break;
        case 10: _t->deleteBind((*reinterpret_cast< std::add_pointer_t<bind_save_t>>(_a[1]))); break;
        case 11: { config_data_t _r = _t->getAllConfigData();
            if (_a[0]) *reinterpret_cast< config_data_t*>(_a[0]) = std::move(_r); }  break;
        case 12: { bind_data_t _r = _t->getAllBindData();
            if (_a[0]) *reinterpret_cast< bind_data_t*>(_a[0]) = std::move(_r); }  break;
        case 13: { config_data_t _r = _t->getSceneConfigDataById((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< config_data_t*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setAllConfigData((*reinterpret_cast< std::add_pointer_t<config_data_t>>(_a[1]))); break;
        case 15: _t->setAllBindData((*reinterpret_cast< std::add_pointer_t<bind_data_t>>(_a[1]))); break;
        case 16: _t->sendSceneData(); break;
        case 17: _t->sendBindData(); break;
        case 18: _t->sendClearSceneData(); break;
        case 19: _t->sendClearBindData(); break;
        case 20: _t->sendGetTimerTask(); break;
        case 21: _t->sendSetTimerTask((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 22: _t->sendCalTime((*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 23: { bool _r = _t->configIsChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: _t->clearConfigChanged(); break;
        case 25: { QByteArray _r = _t->packFrame((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (AppProtocolSetConfig::*)(bool );
            if (_q_method_type _q_method = &AppProtocolSetConfig::recv_scene_data_result; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (AppProtocolSetConfig::*)(const QVector<scene_save_t> & );
            if (_q_method_type _q_method = &AppProtocolSetConfig::sceneListChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (AppProtocolSetConfig::*)(const QVector<bind_save_t> & );
            if (_q_method_type _q_method = &AppProtocolSetConfig::bindListChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (AppProtocolSetConfig::*)(const timer_task_t * );
            if (_q_method_type _q_method = &AppProtocolSetConfig::sigUpdate; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *AppProtocolSetConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppProtocolSetConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN20AppProtocolSetConfigE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppProtocolSetConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void AppProtocolSetConfig::recv_scene_data_result(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AppProtocolSetConfig::sceneListChanged(const QVector<scene_save_t> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AppProtocolSetConfig::bindListChanged(const QVector<bind_save_t> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AppProtocolSetConfig::sigUpdate(const timer_task_t * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
