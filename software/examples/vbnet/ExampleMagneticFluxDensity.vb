Imports System
Imports Tinkerforge

Module ExampleMagneticFluxDensity
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Hall Effect Bricklet 2.0

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim he As New BrickletHallEffectV2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current Magnetic Flux Density
        Dim magneticFluxDensity As Short = he.GetMagneticFluxDensity()
        Console.WriteLine("Magnetic Flux Density: " + magneticFluxDensity.ToString() + " µT")

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
