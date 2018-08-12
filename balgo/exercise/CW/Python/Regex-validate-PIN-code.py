def validate_pin(pin):
    #return true or false
    return str.isdigit(pin) and (len(pin) in [4,6])