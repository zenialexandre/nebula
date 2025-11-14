# nebula.audio

| Functions | Description |
|------|-------------|
|[nebula.audio.setDevice](#nebulaaudiosetdevice)| Sets the audio playback device. |
|[nebula.audio.closeDevice](#nebulaaudioclosedevice)| Closes the current audio device. |
|[nebula.audio.getCurrentDevice](#nebulaaudiogetcurrentdevice)| Gets the name of the current audio device. |
|[nebula.audio.getCurrentDeviceID](#nebulaaudiogetcurrentdeviceid)| Gets the ID of the current audio device. |
|[nebula.audio.getPlaybackDevices](#nebulaaudiogetplaybackdevices)| Gets a list of all available playback devices. |
|[nebula.audio.getRecordingDevices](#nebulaaudiogetrecordingdevices)| Gets a list of all available recording devices. |
|[nebula.audio.getDeviceName](#nebulaaudiogetdevicename)| Gets the name of a specific audio device by ID. |
|[nebula.audio.newSource](#nebulaaudionewsource)| Creates a new audio source from a file. |
|[nebula.audio.play](#nebulaaudioplay)| Plays an audio source. |
|[nebula.audio.pause](#nebulaaudiopause)| Pauses an audio source. |
|[nebula.audio.resume](#nebulaaudioresume)| Pauses an audio source. |
|[nebula.audio.stop](#nebulaaudiostop)| Stops an audio source. |
|[nebula.audio.getSourceLength](#nebulaaudiogetsourcelength)| Gets the length of an audio source in seconds. |
|[nebula.audio.setSourceVolume](#nebulaaudiosetsourcevolume)| Sets the volume of an audio source. |
|[nebula.audio.getSourceVolume](#nebulaaudiogetsourcevolume)| Gets the volume of an audio source. |
|[nebula.audio.isPaused](#nebulaaudioispaused)| Checks if an audio source is paused. |
|[nebula.audio.isPlaying](#nebulaaudioisplaying)| Checks if an audio source is playing. |
|[nebula.audio.destroySource](#nebulaaudiodestroysource)| Destroys an audio source. |
|[nebula.audio.setVolume](#nebulaaudiosetvolume)| Sets the master volume. |
|[nebula.audio.getVolume](#nebulaaudiogetvolume)| Gets the master volume. |

---

## Functions

### nebula.audio.setDevice
Sets the audio playback device.
```lua
nebula.audio.setDevice( deviceId )
```
#### Arguments:
**[ number** deviceId **]** The ID of the audio device to set.

#### Returns:
Nothing.

#### Example:
```lua
local devices = nebula.audio.getPlaybackDevices()
nebula.audio.setDevice(devices[1])
```

---

### nebula.audio.closeDevice
Closes the current audio device.
```lua
nebula.audio.closeDevice()
```
#### Arguments:
None.

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.closeDevice()
```

---

### nebula.audio.getCurrentDevice
Gets the name of the current audio device.
```lua
nebula.audio.getCurrentDevice()
```
#### Arguments:
None.

#### Returns:
**[ string ]** The name of the current audio device.

#### Example:
```lua
local deviceName = nebula.audio.getCurrentDevice()
print("Current device:", deviceName)
```

---

### nebula.audio.getCurrentDeviceID
Gets the ID of the current audio device.
```lua
nebula.audio.getCurrentDeviceID()
```
#### Arguments:
None.

#### Returns:
**[ number ]** The ID of the current audio device.

#### Example:
```lua
local deviceId = nebula.audio.getCurrentDeviceID()
print("Current device ID:", deviceId)
```

---

### nebula.audio.getPlaybackDevices
Gets a list of all available playback devices.
```lua
nebula.audio.getPlaybackDevices()
```
#### Arguments:
None.

#### Returns:
**[ table ]** A table containing all available playback device IDs.

#### Example:
```lua
local devices = nebula.audio.getPlaybackDevices()
for i, deviceId in ipairs(devices) do
    local name = nebula.audio.getDeviceName(deviceId)
    print(i, deviceId, name)
end
```

---

### nebula.audio.getRecordingDevices
Gets a list of all available recording devices.
```lua
nebula.audio.getRecordingDevices()
```
#### Arguments:
None.

#### Returns:
**[ table ]** A table containing all available recording device IDs.

#### Example:
```lua
local devices = nebula.audio.getRecordingDevices()
for i, deviceId in ipairs(devices) do
    local name = nebula.audio.getDeviceName(deviceId)
    print(i, deviceId, name)
end
```

---

### nebula.audio.getDeviceName
Gets the name of a specific audio device by ID.
```lua
nebula.audio.getDeviceName( deviceId )
```
#### Arguments:
**[ number** deviceId **]** The ID of the audio device.

#### Returns:
**[ string ]** The name of the audio device.

#### Example:
```lua
local devices = nebula.audio.getPlaybackDevices()
local deviceName = nebula.audio.getDeviceName(devices[1])
print("First device:", deviceName)
```

---

### nebula.audio.newSource
Creates a new audio source from a file.
```lua
nebula.audio.newSource( filePath )
```
#### Arguments:
**[ string** filePath **]** Path to the audio file.

#### Returns:
**[ number ]** The ID of the created audio source, or -1 if failed.

#### Example:
```lua
local musicId = nebula.audio.newSource("resources/audio/background_music.wav")
```

---

### nebula.audio.play
Plays an audio source.
```lua
nebula.audio.play( sourceId, loop )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source to play,  
**[ boolean** loop **]** (optional) Whether to loop the audio. Default is false.

#### Returns:
Nothing.

#### Example:
```lua
local soundId = nebula.audio.newSource("resources/audio/jump.wav")
nebula.audio.play(soundId) -- Play once
nebula.audio.play(musicId, true) -- Play with looping
```

---

### nebula.audio.pause
Pauses an audio source.
```lua
nebula.audio.pause( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source to pause.

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.pause(musicId)
```

---

### nebula.audio.resume
Pauses an audio source.
```lua
nebula.audio.resume( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source to resume.

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.resume(musicId)
```

---

### nebula.audio.stop
Stops an audio source.
```lua
nebula.audio.stop( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source to stop.

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.stop(musicId)
```

---

### nebula.audio.getSourceLength
Gets the length of an audio source in bytes.
```lua
nebula.audio.getSourceLength( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source.

#### Returns:
**[ number ]** The length of the audio source in bytes.

#### Example:
```lua
local length = nebula.audio.getSourceLength(musicId)
print("Audio length:", length, "bytes")
```

---

### nebula.audio.setSourceVolume
Sets the volume of an audio source.
```lua
nebula.audio.setSourceVolume( sourceId, volume )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source,  
**[ number** volume **]** Volume level (0.0 to 1.0).

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.setSourceVolume(musicId, 0.5) -- Set to 50% volume
```

---

### nebula.audio.getSourceVolume
Gets the volume of an audio source.
```lua
nebula.audio.getSourceVolume( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source.

#### Returns:
**[ number ]** The volume level of the audio source (0.0 to 1.0).

#### Example:
```lua
local volume = nebula.audio.getSourceVolume(musicId)
print("Current volume:", volume)
```

---

### nebula.audio.isPaused
Checks if an audio source is paused.
```lua
nebula.audio.isPaused( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source.

#### Returns:
**[ boolean ]** True if the audio source is paused, false otherwise.

#### Example:
```lua
if nebula.audio.isPaused(musicId) then
    print("Music is paused")
end
```

---

### nebula.audio.isPlaying
Checks if an audio source is playing.
```lua
nebula.audio.isPlaying( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source.

#### Returns:
**[ boolean ]** True if the audio source is playing, false otherwise.

#### Example:
```lua
if nebula.audio.isPlaying(musicId) then
    print("Music is currently playing")
end
```

---

### nebula.audio.destroySource
Destroys an audio source and frees its resources.
```lua
nebula.audio.destroySource( sourceId )
```
#### Arguments:
**[ number** sourceId **]** The ID of the audio source to destroy.

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.destroySource(musicId)
```

---

### nebula.audio.setVolume
Sets the master volume for all audio.
```lua
nebula.audio.setVolume( volume )
```
#### Arguments:
**[ number** volume **]** Master volume level (0.0 to 1.0).

#### Returns:
Nothing.

#### Example:
```lua
nebula.audio.setVolume(0.8) -- Set master volume to 80%
```

---

### nebula.audio.getVolume
Gets the master volume.
```lua
nebula.audio.getVolume()
```
#### Arguments:
None.

#### Returns:
**[ number ]** The current master volume level (0.0 to 1.0).

#### Example:
```lua
local masterVol = nebula.audio.getVolume()
print("Master volume:", masterVol)
```

---