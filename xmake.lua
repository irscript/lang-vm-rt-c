add_rules("mode.debug", "mode.release")

set_languages("c17", "c++17")

if(is_mode("release")) then
    set_optimize("fastest")
    add_cxflags("-O3")
end
add_includedirs("./dev/")

--通用程序库
target("Utils")
    set_kind("static")
    add_files("dev/utils/**.cpp")
--编译器
target("airc")
    set_kind("binary")
    add_files("dev/airc/**.cpp")
--虚拟机运行时
target("VMRT")
    set_kind("binary")
    add_files("dev/VMRT/**.cpp")
--反汇编器
target("Disa")
    set_kind("binary")
    add_files("dev/disas/**.cpp")