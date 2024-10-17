const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});

    // Gets files & configures output
    const exe = b.addExecutable(.{ .name = "chip8", .target = target });
    exe.addCSourceFiles(.{ .files = &[_][]const u8{
        "src/chip8.cpp",
        "src/instructions.cpp",
        "src/main.cpp",
        "src/window.cpp",
    }, .flags = &[_][]const u8{} });

    // Gathers remaining C data
    exe.addIncludePath(b.path("include"));
    exe.linkLibCpp();

    // For windows, gets the SDL2 and SDL2_ttf header files, libraries and binaries
    if (target.query.isNativeOs() and target.result.os.tag == .windows) {
        exe.addIncludePath(b.path("lib/SDL2/include"));
        exe.addLibraryPath(b.path("lib/SDL2/lib/x64/"));
        b.installBinFile("lib/SDL2/lib/x64/SDL2.dll", "SDL2.dll");

        exe.addIncludePath(b.path("lib/SDL2_ttf/include/"));
        exe.addLibraryPath(b.path("lib/SDL2_ttf/lib/x64/"));
        b.installBinFile("lib/SDL2_ttf/lib/x64/SDL2_ttf.dll", "SDL2_ttf.dll");
    }
    // Links SDL2 and SDL2_ttf for both (all?) systems
    exe.linkSystemLibrary("SDL2");
    exe.linkSystemLibrary("SDL2_ttf");

    // idk
    b.installArtifact(exe);

    // This *creates* a Run step in the build graph, to be executed when another step is evaluated that depends on it.
    const run_cmd = b.addRunArtifact(exe);
    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    run_cmd.step.dependOn(b.getInstallStep());
    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
