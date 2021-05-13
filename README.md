# drakhtar-i18n

Internationalization Engine built for the [Drakhtar](https://github.com/kyranet/drakhtar).

---

## Build

### Windows

#### Automatic

Double click on the [`windows-setup.cmd`] and the [`windows-build.cmd`] files accordingly. That's all!

> **Note**: You must download [Microsoft PowerShell](https://github.com/PowerShell/PowerShell) to run the scripts, the
built-in Windows PowerShell does not work as it lacks of features needed for them to work.

#### Manual

First, run CMake:

```sh-session
$ cmake -B build
```

Then build the project inside the `build` folder.

[`windows-setup.cmd`]: https://github.com/kyranet/drakhtar-i18n/blob/main/scripts/windows-setup.cmd
[`windows-build.cmd`]: https://github.com/kyranet/drakhtar-i18n/blob/main/scripts/windows-build.cmd
