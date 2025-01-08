import React, { useEffect, useState } from 'react';
import { useLocation } from 'react-router-dom';
import NavWelcome from '../Components/Nav_Welcome';
import Footer from '../Components/Footer';
import AlecHome from '../Components/AlecHome';

export function Confirmation() {
  const location = useLocation();
  const formData = location.state?.formData || {};
  const [visitorName, setVisitorName] = useState('');

  useEffect(() => {
    setVisitorName(formData.name);
  }, [formData.name]);

  return (
    <div className="Home" style={{ minHeight: '100vh', display: 'flex', flexDirection: 'column' }}>
      <nav>
        <NavWelcome />
      </nav>
      
      <div style={{ color: 'white', flex: 1, display: 'flex', justifyContent: 'center', alignItems: 'center', textAlign: 'center', flexDirection: 'column' }}>
        <div style={{ marginBottom: '20px' }}>
          <h3 style ={{fontSize: '30px', marginBottom: '10px'}}>Welcome {visitorName}!</h3>
          <p style={{fontSize: '20px'}}>You have checked in successfully. Please be seated and remember to </p>
          <p style={{fontSize: '20px'}}>check out at the Reception before you leave.</p>
        </div>
        
        <AlecHome />
      </div>
      
      <Footer />
    </div>
  );
}

export default Confirmation;
