import { Routes, Route } from 'react-router-dom';
import Home from './Pages/Home';
import Login from './Pages/Login';
import Location from './Pages/Location';
import Registration from './Pages/Registration';
import SearchBook from './Pages/SearchBook';
import CheckIn from './Pages/CheckIn';
import Confirmation from './Pages/Confirmation';

function App() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/login" element={<Login />} />
        <Route path="/location" element={<Location />} />
        <Route path="/registration" element={<Registration />} />
        <Route path="/searchbook" element={<SearchBook />} />
        <Route path="/checkin" element={<CheckIn />} />
        <Route path="/confirmation" element={<Confirmation />} />
      </Routes>
    </div>
  );
}

export default App;
