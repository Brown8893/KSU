## Importing Necessary Modules
import requests # to get image from the web
import shutil # to save it locally

## Set up the image URL and filename
image_url = "https://www.google.com.tw/url?sa=i&url=https%3A%2F%2Fwww.ksu.edu.tw%2F&psig=AOvVaw38WcaI_8UPB871PfBd6lUi&ust=1606914189588000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCKjdyvvrrO0CFQAAAAAdAAAAABAO"
filename = image_url.split("/")[-1]

# Open the url image, set stream to True, this will return the stream content.
r = requests.get(image_url, stream = True)

# Check if the image was retrieved successfully
if r.status_code == 200:
    # Set decode_content value to True, otherwise the downloaded image file's size will be zero.
    r.raw.decode_content = True
    
    # Open a local file with wb ( write binary ) permission.
    with open(filename,'wb') as f:
        shutil.copyfileobj(r.raw, f)
        
    print('Image sucessfully Downloaded: ',filename)
else:
    print('Image Couldn\'t be retreived')