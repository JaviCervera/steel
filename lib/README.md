# Irrlicht modifications made

The Windows 95 compatible version is compiled using Visual C++ 6, using Irrlicht 1.3.1.

Other versions use Irrlicht SVN, commit **r6734**.

The modifications made to the SVN version of the engine are described here:

## CIrrDeviceOSX.mm

Search for `NSMenu* mainMenu = [[[NSMenu alloc] initWithTitle:@"MainMenu"] autorelease];` and add the following line right before it:

```c++
if (bundleName) {
```

Below that, after the line that contains `[NSApp setMainMenu:mainMenu];`, close the block with a new line containing `}`.

Also, search for `styleMask:NSTitledWindowMask+NSClosableWindowMask+NSResizableWindowMask` and replace with:

```c++
styleMask:NSTitledWindowMask+NSClosableWindowMask+NSMiniaturizableWindowMask
```