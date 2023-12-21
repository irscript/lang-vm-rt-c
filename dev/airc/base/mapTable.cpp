#include "mapTable.hpp"

namespace air
{
    std::map<std::string, TkKeyWord> MapTable::mapKey;  // 普通关键字映射表
    std::map<std::string, TkAnnotate> MapTable::mapAnn; // 注解关键字映射表
    std::map<TkOpEnum, int32_t> MapTable::mapOp;        // 操作符优先级映射
    void MapTable::init()
    {
        initMapKey();
        initMapAnn();
        initMapOp();
    }

    void MapTable::initMapKey()
    {
        mapKey.insert({"package", TkKeyWord::Package});
        mapKey.insert({"require", TkKeyWord::Require});
        mapKey.insert({"using", TkKeyWord::Using});

        mapKey.insert({"void", TkKeyWord::Void});
        mapKey.insert({"bool", TkKeyWord::Bool});

        mapKey.insert({"int8", TkKeyWord::Int8});
        mapKey.insert({"int16", TkKeyWord::Int16});
        mapKey.insert({"int32", TkKeyWord::Int32});
        mapKey.insert({"int64", TkKeyWord::Int64});

        mapKey.insert({"uint8", TkKeyWord::UInt8});
        mapKey.insert({"uint16", TkKeyWord::UInt16});
        mapKey.insert({"uint32", TkKeyWord::UInt32});
        mapKey.insert({"uint64", TkKeyWord::UInt64});

        mapKey.insert({"sint", TkKeyWord::SInt});
        mapKey.insert({"uint", TkKeyWord::UInt});
        mapKey.insert({"uintptr", TkKeyWord::Uintptr});

        mapKey.insert({"flt32", TkKeyWord::Flt32});
        mapKey.insert({"flt64", TkKeyWord::Flt64});

        mapKey.insert({"string", TkKeyWord::String});
        mapKey.insert({"cstring", TkKeyWord::CString});
        mapKey.insert({"char", TkKeyWord::Char});

        mapKey.insert({"any", TkKeyWord::Any});

        mapKey.insert({"null", TkKeyWord::Null});

        mapKey.insert({"false", TkKeyWord::False});
        mapKey.insert({"true", TkKeyWord::True});

        mapKey.insert({"in", TkKeyWord::In});

        mapKey.insert({"break", TkKeyWord::Break});
        mapKey.insert({"continue", TkKeyWord::Continue});
        mapKey.insert({"goto", TkKeyWord::Goto});
        mapKey.insert({"return", TkKeyWord::Return});

        mapKey.insert({"do", TkKeyWord::Do});
        mapKey.insert({"while", TkKeyWord::While});
        mapKey.insert({"for", TkKeyWord::For});
        mapKey.insert({"foreach", TkKeyWord::Foreach});

        mapKey.insert({"if", TkKeyWord::If});
        mapKey.insert({"elsif", TkKeyWord::Elsif});
        mapKey.insert({"else", TkKeyWord::Else});

        mapKey.insert({"switch", TkKeyWord::Switch});
        mapKey.insert({"case", TkKeyWord::Case});
        mapKey.insert({"default", TkKeyWord::Default});

        mapKey.insert({"private", TkKeyWord::Private});
        mapKey.insert({"protected", TkKeyWord::Protected});
        mapKey.insert({"public", TkKeyWord::Public});
        mapKey.insert({"const", TkKeyWord::Const});

        mapKey.insert({"enum", TkKeyWord::Enum});
        mapKey.insert({"union", TkKeyWord::Union});
        mapKey.insert({"struct", TkKeyWord::Struct});
        mapKey.insert({"entrust", TkKeyWord::Entrust});
        mapKey.insert({"class", TkKeyWord::Class});
        mapKey.insert({"interface", TkKeyWord::Interface});

        mapKey.insert({"this", TkKeyWord::This});
        mapKey.insert({"super", TkKeyWord::Super});
        mapKey.insert({"friend", TkKeyWord::Friend});

        mapKey.insert({"new", TkKeyWord::New});
        mapKey.insert({"sizeof", TkKeyWord::Sizeof});
        mapKey.insert({"typeof", TkKeyWord::Typeof});
        mapKey.insert({"instanceof", TkKeyWord::Instanceof});
        mapKey.insert({"cast", TkKeyWord::Cast});

        mapKey.insert({"try", TkKeyWord::Try});
        mapKey.insert({"catch", TkKeyWord::Catch});
        mapKey.insert({"finally", TkKeyWord::Finally});
        mapKey.insert({"throw", TkKeyWord::Throw});

        mapKey.insert({"await", TkKeyWord::Await});
        mapKey.insert({"synched", TkKeyWord::Synched});
    }

    void MapTable::initMapAnn()
    {
        mapAnn.insert({"@file", TkAnnotate::File});
        mapAnn.insert({"@func", TkAnnotate::Func});
        mapAnn.insert({"@line", TkAnnotate::Line});

        mapAnn.insert({"@buildin", TkAnnotate::Buildin});
        mapAnn.insert({"@async", TkAnnotate::Async});
        mapAnn.insert({"@volatile", TkAnnotate::Volatile});

        mapAnn.insert({"@static", TkAnnotate::Static});
        mapAnn.insert({"@final", TkAnnotate::Final});

        mapAnn.insert({"@inline", TkAnnotate::Inline});
        mapAnn.insert({"@virtual", TkAnnotate::Virtual});
        mapAnn.insert({"@override", TkAnnotate::Override});
        mapAnn.insert({"@operator", TkAnnotate::Operator});
    }

    void MapTable::initMapOp()
    {
        int32_t max = 1000; // 最大优先级
        /*
        mapOp.insert({TkOpEnum::Dot, max}); // .
        --max;
        mapOp.insert({TkOpEnum::Plus2, max});      // ++
        mapOp.insert({TkOpEnum::Minus2, max});     // --
        mapOp.insert({TkOpEnum::LogicalNot, max}); // !
        mapOp.insert({TkOpEnum::BitNot, max});     // ~
        */
        --max;
        mapOp.insert({TkOpEnum::Multiply, max}); // *
        mapOp.insert({TkOpEnum::Divide, max});   // /
        mapOp.insert({TkOpEnum::Modulus, max});  // %
        --max;
        mapOp.insert({TkOpEnum::Plus, max});  // +
        mapOp.insert({TkOpEnum::Minus, max}); // -
        --max;
        mapOp.insert({TkOpEnum::Shl, max});  // <<
        mapOp.insert({TkOpEnum::ShrA, max}); // ->>
        mapOp.insert({TkOpEnum::ShrL, max}); // >>
        mapOp.insert({TkOpEnum::ShlR, max}); // <<)
        mapOp.insert({TkOpEnum::ShrR, max}); // >>(
        --max;
        mapOp.insert({TkOpEnum::LE, max}); // <=
        mapOp.insert({TkOpEnum::LT, max}); // <
        mapOp.insert({TkOpEnum::GE, max}); // >=
        mapOp.insert({TkOpEnum::GT, max}); // >
        --max;
        mapOp.insert({TkOpEnum::EQ, max}); // ==
        mapOp.insert({TkOpEnum::NE, max}); // !=
        --max;
        mapOp.insert({TkOpEnum::BitAnd, max}); // &
        --max;
        mapOp.insert({TkOpEnum::BitXOr, max}); // ^
        --max;
        mapOp.insert({TkOpEnum::BitOr, max}); // |
        --max;
        mapOp.insert({TkOpEnum::LogicalAnd, max}); // &&
        --max;
        mapOp.insert({TkOpEnum::LogicalOr, max}); // ||
        /*--max;
        mapOp.insert({TkOpEnum::Ques, max}); // ?*/
        --max;
        mapOp.insert({TkOpEnum::Assign, max});         // =
        mapOp.insert({TkOpEnum::PlusAssign, max});     // +=
        mapOp.insert({TkOpEnum::MinusAssign, max});    // -=
        mapOp.insert({TkOpEnum::MultiplyAssign, max}); // *=
        mapOp.insert({TkOpEnum::DivideAssign, max});   // /=
        mapOp.insert({TkOpEnum::ModulusAssign, max});  // %=
        mapOp.insert({TkOpEnum::ShlAssign, max});      // <<=
        mapOp.insert({TkOpEnum::ShrLAssign, max});     // >>=
        mapOp.insert({TkOpEnum::ShrAAssign, max});     // ->>=
        mapOp.insert({TkOpEnum::ShlRAssign, max});     // <<)=
        mapOp.insert({TkOpEnum::ShrRAssign, max});     // >>(=
        mapOp.insert({TkOpEnum::BitAndAssign, max});   // &=
        mapOp.insert({TkOpEnum::BitOrAssign, max});    // |=
        mapOp.insert({TkOpEnum::BitXOrAssign, max});   // ^=
        mapOp.insert({TkOpEnum::BitNotAssign, max});   // ~=
    }
}