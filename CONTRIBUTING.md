# Contributing to CORE/3
First of all thanks for your interest in CORE/3.  

Since CORE/3 is a small project still in active development so the codebase and architecture still may change as it grows.  

Before contributing to CORE/3 i would recommend you familiarize yourself with the kernel by building and booting it.  

## Contributing
Contributions are welcome in all areas of the kernel such as:
- Drivers
- Functionality
- Documentation

## Code
CORE/3 is primaraly written in C and x86 Assembly C++ is allowed where useful.  

## Testing

Before submitting a pull request:

Make sure the project builds successfully.
Boot the kernel and test the affected functionality.
Test existing functionality that could reasonably be affected by your changes.

If hardware is required for testing and you cannot test on real hardware, state what environment you used instead.

## Pull Requests

Pull requests should:

Clearly describe what was changed.
Explain why the change was made.
Include relevant testing information.
Keep unrelated changes out of the pull request.

Small fixes and improvements can be submitted directly as pull requests.

## Issues

When reporting a bug, include:

What you expected to happen.
What actually happened.
Steps to reproduce the problem.
Your build environment where relevant.
Any useful kernel output or error messages.

For hardware-related problems, include the hardware configuration if known.

## Development Philosophy

CORE/3 is intended to remain a relatively small and understandable kernel.

When proposing new functionality, consider whether it fits the project's current scope and architecture rather than adding complexity simply for the sake of having a feature.


## License

By contributing to CORE/3, you agree that your contributions will be licensed under the same license as the project.

CORE/3 is licensed under the MIT License.
  
