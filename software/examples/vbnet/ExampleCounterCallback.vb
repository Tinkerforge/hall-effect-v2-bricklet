Imports System
Imports Tinkerforge

Module ExampleCounterCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Hall Effect Bricklet 2.0

    ' Callback subroutine for counter callback
    Sub CounterCB(ByVal sender As BrickletHallEffectV2, ByVal counter As Integer)
        Console.WriteLine("Counter: " + counter.ToString())
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim he As New BrickletHallEffectV2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Configure counter with ±3000µT threshold and 10ms debounce
        he.SetCounterConfig(3000, -3000, 10000)

        ' Register counter callback to subroutine CounterCB
        AddHandler he.CounterCallback, AddressOf CounterCB

        ' Set period for counter callback to 0.1s (100ms)
        he.SetCounterCallbackConfiguration(100, True)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
