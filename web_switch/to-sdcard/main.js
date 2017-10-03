$(function() {
    function setCurrentState(state) {
    	var toggleButton = $('[data-element="toggle-led"]');

        switch(state) {
            case 'on':
	            $.ajax({
	                url: '/?state=on',
	                dataType: 'json',
	                success: function(response) {
						toggleButton.text(toggleButton.data('turnOff'));
						localStorage.setItem('state', response['state']);
	                }
	            });             
                break;

            case 'off':
	            $.ajax({
	                url: '/?state=off',
	                dataType: 'json',
	                success: function(response) {
						toggleButton.text(toggleButton.data('turnOn'));
						localStorage.setItem('state', response['state']);
	                }
	            });             
                
                break;
        }     	
    }

    $(document).on('click', '[data-element="toggle-led"]', function() {
        var _this =  this, prevState = localStorage.getItem('state');

        if (prevState === 'on') {
           setCurrentState('off');

        } else {
            setCurrentState('on');                  
         }
    });

    // Set current and update state
    setCurrentState(localStorage.getItem('state'));
});

