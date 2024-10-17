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
    exe.linkSystemLibrary("libsystemd");

    // sdl2
    if (target.query.isNativeOs() and target.result.os.tag == .linux) {
        exe.linkSystemLibrary("SDL2");
        exe.linkSystemLibrary("SDL2_ttf");
        exe.linkLibC();
    } else {
        const sdl2_dep = b.dependency("zig_sdl", .{
            .target = target,
            .optimize = .ReleaseFast,
        });
        const sdl2_artifact = sdl2_dep.artifact("sdl2");
        exe.linkLibrary(sdl2_artifact);
    }

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
