import React, { useState, useEffect } from 'react';
import Navbar from '../Components/Navbar';
import NavWelcome from '../Components/Nav_Welcome';
import Footer from '../Components/Footer';
import NewVisButton from '../Components/NewVisButton';
import OldVisButton from '../Components/OldVisButton';

const Home = () => {
  const [location, setLocation] = useState(null);

  useEffect(() => {
    const storedLocation = localStorage.getItem('selectedLocation');
    if (storedLocation) {
      setLocation(storedLocation);
    }
  }, []);


  return (
    <div className="Home">
      {location ? <NavWelcome /> : <Navbar />}
      <div className="Content" style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', textAlign: 'center', padding: '20px' }}>
        {location ? (
          <>
            <p style={{ marginBottom: '80px', fontSize: '40px' }}>Welcome to SHAUN JACOB</p>
            <div style={{ marginTop: '20px', display: 'flex', flexDirection: 'row', gap: '70px' }}>
              <NewVisButton />
              <OldVisButton />
            </div>
          </>
        ) : (
          <p>Please click on settings icon to configure device location.</p>
        )}
      </div>
      <Footer />
    </div>
  );
}

export default Home;
