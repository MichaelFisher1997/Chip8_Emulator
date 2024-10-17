const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    const exe = b.addExecutable(.{ .name = "chip8", .target = target });
    exe.addCSourceFiles(.{ .files = &[_][]const u8{
        "src/chip8.cpp",
        "src/instructions.cpp",
        "src/main.cpp",
        "src/window.cpp",
    }, .flags = &[_][]const u8{} });
    exe.addIncludePath(b.path("include"));

    exe.linkLibC();
    exe.linkLibCpp();

    // sdl2
    if (target.query.isNativeOs() and target.result.os.tag == .linux) {
        exe.linkSystemLibrary("libsystemd");
    } else {
        exe.addIncludePath(b.path("lib/SDL2/include"));
        exe.addLibraryPath(b.path("lib/SDL2/lib/x64/"));
        b.installBinFile("lib/SDL2/lib/x64/SDL2.dll", "SDL2.dll");

        exe.addIncludePath(b.path("lib/SDL2_ttf/include/"));
        exe.addLibraryPath(b.path("lib/SDL2_ttf/lib/x64/"));
        b.installBinFile("lib/SDL2_ttf/lib/x64/SDL2_ttf.dll", "SDL2_ttf.dll");
    }
    exe.linkSystemLibrary("SDL2");
    exe.linkSystemLibrary("SDL2_ttf");

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
