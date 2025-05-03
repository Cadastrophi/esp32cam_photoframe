document.addEventListener('DOMContentLoaded', function() {
    const uploadForm = document.getElementById('uploadForm');
    const fileInput = document.getElementById('fileInput');
    const photoDisplay = document.getElementById('photoDisplay');
    const slideshowButton = document.getElementById('slideshowButton');
    const photoTakingModeButton = document.getElementById('photoTakingModeButton');
    const specialPicButton = document.getElementById('specialPicButton');
    const backButton = document.getElementById('backButton');

    uploadForm.addEventListener('submit', function(event) {
        event.preventDefault();
        const file = fileInput.files[0];
        if (file) {
            const formData = new FormData();
            formData.append('file', file);

            fetch('/upload', {
                method: 'POST',
                body: formData
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    alert('File uploaded successfully!');
                    displayImage(data.filePath);
                } else {
                    alert('File upload failed.');
                }
            })
            .catch(error => {
                console.error('Error:', error);
            });
        }
    });

    function displayImage(filePath) {
        photoDisplay.src = filePath;
        photoDisplay.style.display = 'block';
    }

    slideshowButton.addEventListener('click', function() {
        // Implement slideshow functionality
    });

    photoTakingModeButton.addEventListener('click', function() {
        // Implement photo taking mode functionality
    });

    specialPicButton.addEventListener('click', function() {
        // Implement special picture functionality
    });

    backButton.addEventListener('click', function() {
        // Implement back functionality
    });
});