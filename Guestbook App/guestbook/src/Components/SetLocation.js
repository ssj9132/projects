const setLoc = () => {
    const selectedLocation = localStorage.getItem('selectedLocation');
  
    return (
      <p style={{ 
        color: 'white', 
        fontFamily: 'Arial, sans-serif', 
        fontSize: 'larger',
        marginLeft: 'auto', 
        marginRight: '30px', 
      }}>
        {selectedLocation}
      </p>
    );
  }
  
  export default setLoc;
  