add_rules("mode.debug", "mode.release")

set_languages("c17", "c++17")

if(is_mode("release")) then
    set_optimize("fastest")
    add_cxflags("-O3")
end
add_includedirs(".")

--通用程序库
target("Utils")
    set_kind("static")
    add_files("utils/**.cpp")
--编译器
target("airc")
    set_kind("binary")
    add_files("airc/**.cpp")
--虚拟机运行时
target("VMRT")
    set_kind("binary")
    add_files("VMRT/**.cpp")
--反汇编器
target("Disa")
    set_kind("binary")
    add_files("disas/**.cpp")