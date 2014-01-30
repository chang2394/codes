
ill mod_power(ill a, ill b) {
    ill x = 1, y = a;
    while ( b > 0 ) {
        if ( b%2 == 1 ) {
            x = (x*y)%MOD;
        }
        y = (y*y)%MOD;
        b /= 2;
    }
    return x;
}
