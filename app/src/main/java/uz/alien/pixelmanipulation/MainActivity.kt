package uz.alien.pixelmanipulation


import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import uz.alien.glecy.NativeLib


class MainActivity : AppCompatActivity() {

    private val context = this

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(NativeLib(context))
    }
}